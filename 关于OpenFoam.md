- 东岳流体：http://dyfluid.com/
- CFD中的张量公式：http://dyfluid.com/docs/tensor.html
- OpenFOAM里面3个最基本的求解器：
  - laplacianFoam（http://dyfluid.com/laplacianFoam.html）
  - scalarTransportFoam（http://dyfluid.com/scalarTransportFoam.html）
  - potentialFoam（http://dyfluid.com/potentialFoam.html）
- simple求解器：http://dyfluid.com/simplefoam.html
- icoFoam求解器：http://dyfluid.com/icoFoam.html
- interFoam求解器：http://dyfluid.com/interFoam.html

- CFD的壁面函数：http://dyfluid.com/wallFunction.html

- 计算流体力学 ：https://www.zhihu.com/collection/747809765

**OpenFOAM求解器开发（编译、库、包含、laplacianFoam）**：https://www.zybuluo.com/daidezhi/note/385554

**商业软件划分的网格向OpenFOAM转换应注意的问题**http://blog.sina.com.cn/s/blog_5fdfa7e60100dsiq.html

 **openfoam里的网格对象fvMesh** https://zhulianhua.github.io/2016/10/06/of-fvMesh/

 **openfoam C++代码的特性**https://blog.csdn.net/imastrid/article/details/119924469?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-0.pc_relevant_paycolumn_v3&spm=1001.2101.3001.4242.1&utm_relevant_index=3


 **openfoam里的网格对象fvMesh** https://zhulianhua.github.io/2016/10/06/of-fvMesh/

  **复杂初边值处理方案**：https://zhuanlan.zhihu.com/p/381296788


 **几个环境变量：**

  
$FOAM_TUTORIALS：OpenFOAM算例目录,包含所有OpenFOAM官方教程算例---tut

$FOAM_SRC：OpenFOAM总库源代码目录，finiteVolume、mesh等库源代码目录---src

$FOAM_APP：OpenFOAM应用源代码目录，包含solvers、test和utilities（已经编译好的)---app

$FOAM_APPBIN：（platforms文件夹下）OpenFOAM标准应用目标代码目录，在make文件夹下的file文件里指定生成exe文件的位置就是这里(存放求解器目录和库的目录)

$(FOAM_USER_APPBIN):用户自定义求解器编译后生成的可执行程序exe和库lib的位置，在openfoan/yantao-6/platforms...下

$FOAM_RUN：用户算例目录，存放算例---run


**离散**：
ddt：时间项
laplacian：扩散项
div：对流项


**求解器基本架构:**
newApp.C		newApp求解器顶层源代码
createFields.H		变量场的声明和初始化
files			按行存储所有源代码文件名(c文件)，最后一行用来指定目标代码EXE的名称和存放位置
options			设定查找头文件和库的路径EXE_INC和需要链接的库EXE_LIBS，对于链接的 单个 库文件，必须通过标示符-l指定，并且去掉lib前缀以及.so后缀，例如：libnew.so，应该使用-lnew。

**openfoam中的数据类型**
- 基础：标量 scalar, 向量 vector, 张量 tensor，对错型 bool，整形 label
- 场 field class类：typedef field<scalar> saclarField，typedef field<vector> vectorField,typedef field<tensor> tensorField
- 几何场类 GeometricField class:volScalarField 体标 量场，volVectorField 体向量场，volTensorField 体张量场; 相比 field class 多了纪录场位置 的相关信息,记录了在什么样的网格上有量 a 的相关信息或数据.

**编写自己的求解器**
1. 创建一个空的求解器


  ```cpp
   foamNewApp mySolver
   ```
   这样就可以创建一个路径，里面有一个叫做mySolver.C的文件，文件里有写好的文件头和主函数的框子等等。这个源文件外头还有一个Make路径，Make里面也已经有了现成的files和options 文件了。
   
   值得注意的是，这句命令最好在applications目录下运行，这样新生成的solver会和系统的求解器放在一个路径下，避免新手搞不定编译的问题。

2. 创建网格对象
   
  实际上是根据生成的网格创建一个对象。一般不需要自己搞，只要一句话:
   ```cpp
   #include "createMesh.H"
   ```
   这句话应该是将求解器路径下的/constant/polyMesh下的网格文件读入程序，编程一个对象。

3. 读取初场和系数：creatFields.H
   
  往第二步网格上放变量和系数，就是指定每个cv里的变量是多少。在求解器里也只是一句话：
   ```cpp
   #include "createFields.H"
   ```
   但实际上没那么easy，因为具体要读取什么变量和系数每个求解器不太一样，有的时候所以要自己修改一些内容。所以我们在.C文件的同一个路径下新建一个creatFields.H文件。里面的内容，按照我们的示例方程也就是$$\frac{\partial \theta}{\partial t}=\nabla\cdot(\kappa\nabla(h+z))\\\theta = g(h)$$来写。那么我们要读入的变量就是 h，要读入的系数就是 $\kappa$.

   变量和系数的读入（和读出，因为有些量，不只是变量是要输出来给人看的）在of里通过对象注册机来完成。新手完全没必要琢磨这是个啥，只要知道变量和系数是这样写入写出的就vans了。

  (1). 读取系数
   
  先读$\kappa$，仿照scalarTransportFoam的写法：
  ```cpp
   Info<< "Reading transportProperties\n" << endl;
   IOdictionary transportProperties
  (
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
  );
   ```
  这一段原封不动抄进去就行。到这里是创建了一个IOdictionary的对象，叫做TransportProperties。创建的时候就用IoObject来初始化。如何初始化呢？首先从从/constant路径下的叫做"transportProperties"的文件里读入数据，这分别是IoObject里面前两行的意思。剩下的就是把这个东西注册（也就是写到）mesh上，mesh是第二步里创建出来的东西。

ok，现在我们有一个对象叫做transportProperties，这个对象是IOdictionary类的，也就拥有了这个类下的各种函数。那么我们要用的就是查找具体系数的功能。虽然这个例子里只有一个系数，看上去多次一举。但是真正的求解器会有若干个系数，所以要分别处理。写入$\kappa$的语句是：
```cpp
Info<< "Reading diffusivity DT\n" << endl;
dimensionedScalar kappa
(
    transportProperties.lookup("kappa")
);
```

可以看到，我们创建了一个对象叫做kappa，是一个dimensionedScalar类的对象。这个对象初始化的时候值从哪来？使用lookup函数从文件里找来。这个函数从哪里来？从我们上一步创建的transportProperties里来。上一步我们说，transportProperties是个IOdictionary类的对象，lookup函数也是从这个类里来的。


  (2). 读取初始场

  ok，接下来搞初场。我们的方程只有一个变量，也就只有一个初场。这个初场放在./0路径下面，就叫做h。读取的方式跟上面差不多。上面我们读取系数的时候创建了一个系数属于的对象，那么现在我们也要创建一个变量属于的对象。此处是h，是个标量所以我们要创建一个标量场volScalarField。在of里，写成：

  ```cpp
  Info<< "Reading field T\n" << endl;
volScalarField h
(
    IOobject
    (
        "h",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
  ```

对象注册机的写详细说明参阅资料:https://www.cfd-china.com/topic/2153/openfoam%E4%B8%AD%E7%9A%84%E6%B3%A8%E5%86%8C%E6%9C%BA%E5%88%B6%E6%98%AF%E4%BB%80%E4%B9%88%E6%84%8F%E6%80%9D?lang=zh-CN https://www.dazhuanlan.com/2019/09/30/5d9197ed9f190/ https://marinecfd.xyz/post/openfoam-object-registry/#%E6%A0%91%E7%8A%B6%E7%BB%93%E6%9E%84%E7%9A%84%E7%AE%A1%E7%90%86

4. 方程离散

接下来的任务是创建一个离散的方程组。方程组在of中一般以fvVectorMatrix或者fvScalarMatrix的类的对象存在。前者是用来储存速度这类矢量，压力、温度、vof相函数等标量储存在后者。此处我们创建一个fvScalarMatrix的对象hEqn：

```cpp
 fvScalarMatrix hEqn
 (
    fvm::ddt(h)
    == fvm::laplacian(kappa, h)
);
```

可以看见这里的写法很类似与真实的数学写法。

常见的微分算符，其实就是瞬态微分，散度和laplace，分别写作ddt,div,laplacian。这三者又分别属于fvm和fvc两个命名空间，fvm是隐式，fvc是显式，取决与需要的离散格式。
当然还有一个要注意的地方是时间循环。在of里没有真正的稳态计算（？）所有的问题都是瞬态的，只是在稳态问题中可以放大时间步让方程迅速收敛到稳态而已（此处存疑）。所以在写稳态求解器的时候一样要写上瞬态项。

既然有瞬态项就必须有步进策略，而在of中步进一般由simple算法的框架来完成，其实这种简单求解器完全不需要simple算法，此处只是为了通用性而调用simple而已。

具体的语句是，在此前，就使用mesh生成一个叫做simple的对象，属于simpleControl类，语句是：
```cpp
simpleControl simple(mesh);
```
接下来，在上述离散步骤的外面需要套一个循环：
```cpp
while (simple.loop(runTime))
{
}
```
5. 方程求解

构建好方程组之后，只需要一个简单的solve就能搞定求解：
```cpp
hEqn.solve();
```
还有两种求解的语句调用形式：
```cpp
fvVectorMatrix UEqn(...);
solve(UEqn == -fvc::grad(p));
```
6. 结果输出
  
每个时间步都需要把结果输出来，所以加上一句：
```cpp
runTime.write();
```
整个求解器就算初具雏形了。看一下整体的样子：

```cpp
#include "fvCFD.H"// 必备头文件
#include "fvOptions.H"// 与源项有关，目前不涉及可以删掉
#include "simpleControl.H"// 时间推进有关
int main()// 主函数
{
    #include "setRootCaseLists.H"//必备
    #include "createTime.H"//创建时间对象
    #include "createMesh.H"//创建mesh 后续频繁使用
    simpleControl simple(mesh);//创建simple对象，用于控制时间推进
    #include "createFields.H"//创建场，读取初场和系数
    Info<< "\nCalculating h transport\n" << endl;//提示计算开始
    #include "CourantNo.H"// 计算库朗数
    while (simple.loop(runTime))// 时间循环开始
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;//输出当前时间
        while (simple.correctNonOrthogonal())//非正交修正，本求解器不涉及可以删掉
        {
            fvScalarMatrix hEqn//创建线性方程组
            (
                fvm::ddt(h)
              == fvm::laplacian(kappa, h)
            );
            hEqn.relax();//松弛，可以删掉
           // fvOptions.constrain(hEqn);//与源项有关，目前不涉及，可以删掉
            hEqn.solve();//求解
            //fvOptions.correct(h);//同上
        }
        runTime.write();//输出
    }
    Info<< "End\n" << endl;//提示计算结束
    return 0;
}
```
接下来要做的是把源代码编程一个可执行程序。所有的solver都是可执行程序。所以需要编译。编译通过wmake即可，之前的Make文件夹就是为这个准备的。

7. 编译
  
使用wmake，这个of自带的编译系统即可。因为之前我们使用foamNewApp命令生成了Make，内容都不用修改。直接在在当前求解器目录下：
```c
wmake
```
就vans了。
这部分有个很强的教程可以参考。https://www.zybuluo.com/gunshooter/note/1716545

8. 运行求解器
   
求解的前提是准备**网格+初场**。我不太喜欢blockMesh，又学不太会snappyHexMesh，所以网格都用商软来画，画完转换一下。这部分的内容见另一个笔记：https://www.zybuluo.com/gunshooter/note/1716545

**三个求解器例子**

**例1：OpenFOAM>>solver>>basic>>laplacianFoam**

```cpp
//createFields.H


//－屏幕提示。Info 等价于 C++中std::cout,Info间接调用cout
    Info<< "Reading field T\n" << endl;  
 
//－声明一个标量场,网格中心存储变量。该场是通过读入文件(IOobject and MUST_READ)进行设置,并根据controlDict中的设置进行自动write,由write.H中的runTime.write()来执行write();。
 
    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
 
    //- 提示读入参数控制文件
    Info<< "Reading transportProperties\n" << endl;
    //- 参数控制文件声明过文件形式读入
    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties", //文件名字
            runTime.constant(), //文件位置，case文件夹中constant子文件夹
            mesh,              
            IOobject::MUST_READ,//通过read一个文件，初始化
            IOobject::NO_WRITE  //并不根据时间对文件进行写
        )
    );
 
    //－提出读入扩散律
    Info<< "Reading diffusivity DT\n" << endl;
 
    //－通过查询参数控制文件，初始化带有单位的标量，lookup中的“DT”为关键字
    dimensionedScalar DT
    (
        transportProperties.lookup("DT")
    );
```
```cpp
// laplacianFoam.C


#include "fvCFD.H"  //-cfd头文件，包括大多数cfd计算需要的头文件，在src » finiteVolume » cfdTools » general » include
 
 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//主程序入口
int main(int argc, char *argv[])
{
//设置rootcase，根据输入参数argc 和 argv对
#   include "setRootCase.H"
 
//－创建时间，下面的runTime控制
#   include "createTime.H"
 
//创建网格，根据constant文件中polyMesh文件夹中的网格数据，创建网格对象mesh，位于src » OpenFOAM » include
#   include "createMesh.H"
 
//创建场对象，在前面已经说明
#   include "createFields.H"
 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//提示计算温度分布
    Info<< "\nCalculating temperature distribution\n" << endl;
//计算主控制流程
    for (runTime++; !runTime.end(); runTime++)
    {
//提示当前计算时间
        Info<< "Time = " << runTime.timeName() << nl << endl;
//读入simple算法参数，位于
 
src » finiteVolume » cfdTools » general » include
 
#       include "readSIMPLEControls.H"
//对于网格非正交循环修正。
        for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
        {
//求解拉普拉斯方程,这里的solve是Foam空间的全局函数，内参数为fvMatrix，fvm表示隐式离散，返回有限容积稀疏矩阵类fvMatrix对象，具体对象中内容，以后说明
            solve
            (
                fvm::ddt(T) - fvm::laplacian(DT, T)
            );
        }
//对求解变量进行写
#       include "write.H"
//提示执行时间及CPU耗时
        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }
//提示程序结束
    Info<< "End\n" << endl;
 
    return(0);
}
```
```cpp
//write.H


if (runTime.outputTime())
{
    volVectorField gradT = fvc::grad(T);  //计算温度梯度，向量场
 
   //声明3个变量，分别以gradT的三个方向的分量进行初始化。
 
    volScalarField gradTx
    (
        IOobject
        (
            "gradTx", //变量名字
            runTime.timeName(), //位置
            mesh,               //mesh，主要用于对象注册，根据runTime进行写
            IOobject::NO_READ,  //
            IOobject::AUTO_WRITE //自动写
        ),
        gradT.component(vector::X)  //用场初始话，vector::X 枚举变量，可直接写0 //gradT.component(0)
    );
 
    volScalarField gradTy
    (
        IOobject
        (
            "gradTy",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        gradT.component(vector::Y)
    );
 
    volScalarField gradTz
    (
        IOobject
        (
            "gradTz",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        gradT.component(vector::Z)
    );
 
    //对场进行写
    runTime.write();
}
```
Tips：runTime是类Time的一个对象，runTime.timeName()其实就是当前运行到的物理时间（非稳态物理问题的时间），你程序运行到了5.1 s，runTime.timeName()就会将字符串“5.1”返回给你，OpenFOAM在对不同时刻的数据进行存取的时候就是靠着这个字符串。runTime.constant()返回的就是case下那个constant文件夹的名字，这个名字可以改的，默认为constant。OpenFOAM根据case文件夹里面的system/controlDict里面对输出的设置来确定当前时刻时候输出，如果当前时刻输出的话，outputTime()就为true，就输出数据了。


**例2：OpenFOAM>>solver>>basic>>potentialFoam**
```cpp
//creatField.H

//提示创建压力场
 
Info<< "Reading field p\n" << endl;
 
//压力场为标量场，网格中心存储变量（OpenFOAM用的是非结构化同位网格），下面为创建标量场压力，两个参数IOobject对象和网格对象mesh，IOobject主要从事输入输出控制
    volScalarField p 
    (
        IOobject
        (
            "p",                //压力场初始文件的名字。
            runTime.timeName(), //位置，该位置由case中的system/controlDict中的startTime控制
            mesh,               //网格对象，主要从事对象注册，以便由runTime.write()控制输出
            IOobject::MUST_READ,//该对象由文件读出创建，因此，需要READ
            IOobject::NO_WRITE  //不输出压力场
        ),
        mesh  //压力场所用的网格对象，在createMesh.H创建
    );
 
//压力场初始化为0，单位为上面文件中的单位。dimensionedScalar 为带单位的标量，初始化三个参数，名字，单位，数值。也可采用如下形式
 
//dimensionedScalar("zero",dimensionSet(1,-1,-2,0,0 ,0, 0),0.0);
 
//应当注意，OpenFOAM中的大部分case对动量的求解都是求解的速度场，压力单位初始化时候，一般为除去密度后的值.
 
//dimensionSet中有7个参数，他们依次为质量、长度、时间、温度、摩尔数、安培、坎德拉。
 
  
 
p = dimensionedScalar("zero", p.dimensions(), 0.0);   
 
  
 
//提示读入速度场
 
Info<< "Reading field U\n" << endl;
    //创建速度场，向量场，体心存储变量。
 
volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE  //自动写，根据runTime.write()或者U.write();
        ),
        mesh
    );
 
  
 
//初始化速度场。这里初始化速度为0 ，如果初始化Ux=1，Uy=2，Uz=3 （单位为国际单位）可采用
 
//U = dimensionedVector("0", U.dimensions(), vector(1,2,3));
 
U = dimensionedVector("0", U.dimensions(), vector::zero);
 
  
 
//表面场，phi，界面流率，存储在体之间的交接面上。表面场(surface...)不能和体积场(vol...)
 
//直接计算，因为他们存储在不同地方，大小不同。
 
//可以将体积场转化为表面场（运用fvc::interpolate())
 
//或者由表面场转化为体积场（运用fvc::reconstruct())进行计算。
 
surfaceScalarField phi
    (
        IOobject
        (
            "phi",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
    //U是体积场，运用插值转为表面场和表面积场进行相乘来初始化流率
 
    //mesh.Sf()返回网格交接面面积矢量。
 
    fvc::interpolate(U) & mesh.Sf()
 
);
 
//压力参考cell
    label pRefCell = 0;
 
//压力参考值
    scalar pRefValue = 0.0;
    setRefCell(p, mesh.solutionDict().subDict("SIMPLE"), pRefCell, pRefValue);
   //只有求解区域所有的压力边界都为第二类边界条件是，上面的值才会用到。如果有第一类边界条件，
 
//压力参考值为这点边界值。对于不可压缩流动压力值为相对值，上面的参考值的大小对结果无影响。
```
```cpp
//potentialFoam.C


#include "fvCFD.H"
 
 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
 
//主程序入口
 
int main(int argc, char *argv[])
{
 
//增加新的有效输入参数。
 
argList::validOptions.insert("writep", "");
 
//设置case目录
 
#   include "setRootCase.H"
 
//创建时间，对计算流程进行控制，主要是名为runTime的对象
 
#   include "createTime.H"
 
//创建网格对象mesh
#   include "createMesh.H"
 
//创建场变量，前面已经说过
#   include "createFields.H"
 
//读simple控制参数
#   include "readSIMPLEControls.H"
 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
 
//计算势流提示
 
    Info<< nl << "Calculating potential flow" << endl;
 
//对流率进行调整，以保证方程的连续性
 
    adjustPhi(phi, U, p);
 
//网格非正交性循环，如果网格是正交的，可以设定nNonOrthCorr=1
 
  for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
 
//创建压力方程，该方程为标量稀疏矩阵类
        fvScalarMatrix pEqn
        (
            fvm::laplacian  //拉普拉斯离散，隐式
            (
                dimensionedScalar
                (
                    "1",
                    dimTime/p.dimensions()*dimensionSet(0, 2, -2, 0, 0),
                    1
                ),
                p
            )
         ==
            fvc::div(phi)//速度离散，显示。因为是压力方程，其他变量只能显示
        );
 
//设定压力参考值
 
        pEqn.setReference(pRefCell, pRefValue);
 
//求解压力方程，调用的fvMatrix成员函数
        pEqn.solve();
 
//流率修正，应当注意OpenFOAM中对压力本身求解，而非压力变化值。
 
//关于simple算法和PISO算法的OpenFOAM实现，会在simpleFoam及其icoFoam中详细说明。
 
if (nonOrth == nNonOrthCorr)
        {
            phi -= pEqn.flux();
        }
    }
 
//提示连续性方程求解误差
 
    Info<< "continuity error = "
        << mag(fvc::div(phi))().weightedAverage(mesh.V()).value()
        << endl;
 
//根据表面场重建速度场
 
    U = fvc::reconstruct(phi);
 
//对速度场边界进行修正，主要针对第二类边界条件下的边界场
    U.correctBoundaryConditions();
 
    Info<< "Interpolated U error = "
        << (sqrt(sum(sqr((fvc::interpolate(U) & mesh.Sf()) - phi)))
          /sum(mesh.magSf())).value()
        << endl;
 
    // Force the write
 
//直接对速度进行输出
    U.write();
 
//界面流率输出。注意当前场存储在界面上，phi的大小（个数）和U的大小（个数）不相同的
    phi.write();
 
//如果用户计算是，让输出p，即输入了writep，则输出p
 
    if (args.options().found("writep"))
    {
        p.write();
    }
 
//提示执行时间，cpu时间
 
    Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;
 
//提示程序结束
 
    Info<< "End\n" << endl;
 
//返回0   
 
return(0);
}
```
**例3：OpenFOAM>>solver>>basic>>scalarTransportFoam**
```cpp
//createFields.H


//提示读入温度场
 
Info<< "Reading field T\n" << endl;
 
//温度场创建，标量场，需要初始化文件，下面各项具体含义，参看以前solver的说明
 
volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
 
//提示读入速度场
    Info<< "Reading field U\n" << endl;
 
//速度场创建，各项意义，前面solver说明中已经给出
 
volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
 
//读入参数提示
    Info<< "Reading transportProperties\n" << endl;
 
//根据名字为transportProperties的参数文件构建参数字典，以便查找。
 
IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",//参数字典文件名字
            runTime.constant(),//参数字典文件位置
            mesh,              //网格对象
            IOobject::MUST_READ,//需要读入文件
            IOobject::NO_WRITE //不对文件进行重写
        )
    );
 
//查询参数字典提示
    Info<< "Reading diffusivity D\n" << endl;
 
//参数字典查询，初始化带单位标量DT（温度扩散率）
 
dimensionedScalar DT
    (
        transportProperties.lookup("DT")
    );
 
//创建表面流率场，该文件位于
 
//src » finiteVolume » cfdTools » incompressible
#   include "createPhi.H"
<p>//scalarTransportFoam.C</p>
```
```cpp
scalarTransportFoam.C


#include "fvCFD.H"
 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
 
//主程序入口
 
int main(int argc, char *argv[])
{
 
//设置case目录相关，位于src » OpenFOAM » include
 
#   include "setRootCase.H"
 
  
 
//创建time对象runTime，位于 src » OpenFOAM » include
 
#   include "createTime.H"
 
  
 
//创建网格对象mesh，位于src » OpenFOAM » include
#   include "createMesh.H"
 
//创建场对象，前面已经详述
#   include "createFields.H"
 
 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
 
//提示计算标量传输方程
 
    Info<< "\nCalculating scalar transport\n" << endl;
 
//显示当前courant数，位于src » finiteVolume » cfdTools » incompressible
 
#   include "CourantNo.H"
 
  
 
//计算主流程
 
    for (runTime++; !runTime.end(); runTime++)
    {
 
//显示当前时间（物理时间，非cpu耗时）
        Info<< "Time = " << runTime.timeName() << nl << endl;
 
//读入simple算法控制参数，位于src » finiteVolume » cfdTools » general » include
 
#       include "readSIMPLEControls.H"
 
//网格非正交循环
 
        for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
        {
 
//构造并求解方程
            solve
            (
                fvm::ddt(T)  //非稳态项，隐式离散
              + fvm::div(phi, T) //对流项，隐式离散
              - fvm::laplacian(DT, T) //扩散项，隐式离散
            );
        }
 
        runTime.write(); //求解结果输出，由于采用了注册机制，所有AUTO_WRITE声明的变量，
 
//都会输出
    }
 
    Info<< "End\n" << endl; //提示程序结束
 
    return(0); //返回0
}
```
