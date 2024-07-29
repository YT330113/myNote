# 关于OpenFOAM

## OpenFOAM网上学习资料

[openfoam和面向对象C++看这一篇就够了](https://zhulianhua.github.io/documents/objectOrientation.pdf)

[最全OpenFOAM 学习资料 | Lianhua Zhu's Blog (zhulianhua.github.io)](https://zhulianhua.github.io/2016/09/28/OpenFOAM-Learning-Resources/)

- 苏军伟博客 http://blog.sina.com.cn/openfoamresearch
这显然是最常见的入门学习材料之一了，内容很多，比较全面。
- 东岳流体 http://dyfluid.com/
李东岳的网站，有求解器的详细资料（其实对初学者感觉还是不够详细）。比较其余两个更学术一些。还有一些OF之外的流体力学资料。
- 戴得志的笔记 https://www.zybuluo.com/daidezhi/note/391186
最近（2019.06.13）才发现的一套笔记，流程比较清楚，目的是自定义（并编译使用）求解器，中间的各个步骤都有讲解。内容似乎不是很多，好像作者不是专门做这个的。
- 流沙CAE https://www.cfder.club/
胡坤的博客。之前似乎是在新浪有一个博客的，这个应该是新的。整个博客都是偏工程应用的感觉，这个系列中的OF内容较少，也比较浅显。不过也有一些资料索引，而且也是成体系的一个博客，所以也列在这里。
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

## openfoam中的边界条件

1. 几何边界条件（体现在`constant/polyMesh/boundary`）

- wall
- patch
- empty
- cyclic
- symmetry
2. 物理边界条件(体现在`/0`文件夹下的物理量)

- fixedValue
- zeroGradient
- slip
- noslip
- empty
- symmetry
- cyclic
- coded...

## 文件解析

**OpenFOAM中 controlDict 字典文件解析**https://www.zybuluo.com/daidezhi/note/391186

**OpenFOAM中 fvSchemes 字典文件解析**https://www.zybuluo.com/daidezhi/note/389113

**OpenFOAM中 fvSolution 字典文件解析**https://www.zybuluo.com/daidezhi/note/392250

**openfoam二维多面体网格**https://www.zybuluo.com/daidezhi/note/386328

**OpenFOAM求解器开发（编译、库、包含、laplacianFoam）**：https://www.zybuluo.com/daidezhi/note/385554

**商业软件划分的网格向OpenFOAM转换应注意的问题**http://blog.sina.com.cn/s/blog_5fdfa7e60100dsiq.html

 **openfoam里的网格对象fvMesh** https://zhulianhua.github.io/2016/10/06/of-fvMesh/

 **openfoam C++代码的特性** https://blog.csdn.net/imastrid/article/details/119924469?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-0.pc_relevant_paycolumn_v3&spm=1001.2101.3001.4242.1&utm_relevant_index=3


 **openfoam里的网格对象fvMesh** https://zhulianhua.github.io/2016/10/06/of-fvMesh/

##   **复杂初边值处理方案**：

 https://zhuanlan.zhihu.com/p/381296788

##  几个环境变量：

`$FOAM_TUTORIALS`：OpenFOAM算例目录,包含所有OpenFOAM官方教程算例---tut

`$FOAM_SRC`：OpenFOAM总库源代码目录，finiteVolume、mesh等库源代码目录---src

`$FOAM_APP`：OpenFOAM应用源代码目录，包含solvers、test和utilities（已经编译好的)---app

`$FOAM_APPBIN`：（platforms文件夹下）OpenFOAM标准应用目标代码目录，在make文件夹下的file文件里指定生成exe文件的位置就是这里(存放求解器目录和库的目录)

`$(FOAM_USER_APPBIN)`:用户自定义求解器编译后生成的可执行程序exe和库lib的位置，在openfoan/yantao-6/platforms...下

`$FOAM_RUN`：用户算例目录，存放算例---run

## 离散：

ddt：时间项

laplacian：扩散项

div：对流项。`div`操作符表面看，是计算散度的，实际上，在OpenFAOM中，`div` 操作符的作用是加和，比如说 $\nabla \cdot (UU)$，在OpenFOAM中表示为`fvm::div(phi,U)`，这段代码真正执行的是$\sum_f U_f \phi_f$运算，即将每个网格包含的面上的流率与速度乘积，然后再加起来

div(phi,U): 

> phi is actually the flux through the cells (so it is not a volVectorField, but a surfaceScalarField). For incompressible solver phi=U, but in case of compressible flows, phi=rho*U. This is why phi is used, you only change its definition in createFields.

## 求解器基本架构:

**newApp.C**		newApp求解器顶层源代码
**createFields.H**		变量场的声明和初始化
**files**			按行存储所有源代码文件名(c文件)，最后一行用来指定目标代码EXE的名称和存放位置
**options**			设定查找头文件和库的路径EXE_INC和需要链接的库EXE_LIBS，对于链接的 单个 库文件，必须通过标示符-l指定，并且去掉lib前缀以及.so后缀，例如：libnew.so，应该使用-lnew。

## openfoam中的数据类型

- 基础：标量 scalar, 向量 vector, 张量 tensor，对错型 bool，整形 label

- 场 **field class**类：

  ```cpp
  typedef field<scalar> saclarField;
  typedef field<vector> vectorField;
  typedef field<tensor> tensorField
  ```

- 几何场类 **GeometricField class**:

  ```cpp
  volScalarField 体标量场;
  volVectorField 体向量场;
  volTensorField 体张量场; 
  ```

  相比 field class 多了纪录场位置 的相关信息,记录了在什么样的网格上有量 a 的相关信息或数据.

---

## Boundary Condition inOpenFOAM

就是指明边界上的值和梯度是多少，有时靠给定的值就够了，有时需要结合边界处element内的值来插值

不论什么边界，fixedValue还是fixedGradient，都是一个patch field列表，存储了边界面上的场值

为了完成`updateCoeffs()`函数，要使用`valueInternalCoeffs`, `valueBoundaryCoeffs`, `gradientInternalCoeffs`, 和`gradientBoundaryCoeffs`来==线性化边界条件==。通过这四个函数使边界条件进入离散方程。

- `valueInternalcoeffs`和`valueBoundaryCoeffs`通常用来线性化`div`算子的边界条件，因为该算子需要patch face面上的值.
- `gradientInternalCoeffs`, 和`gradientBoundaryCoeffs`来线性化`laplacian`算子的边界条件,因为该算子需要patch face面上的梯度

### Neumann boundary

由于方向梯度为零，因此这种边界boundary patch上的值是等于boundary element上的值的

**`div`算符：**

需要的是边界面上的值（value），例如，零梯度边界条件的boundary value可以写成
$$
\begin{aligned}
\phi_b&= FluxCb\,\phi_c+FluxVb \\
&= valueInternalCoeffs\,\phi_c+valueBoundaryCoeffs \\
&=1\phi_c+0
\end{aligned}
$$
**`laplacian`算符**：

需要的是边界面上的梯度（gradient），同样对于零梯度：
$$
\begin{aligned}
\nabla \phi_b&=gradientInternalCoeffs\, \phi_c+GradientBoundaryCoeffs\ \\
&=0 \phi_c+0
\end{aligned}
$$

### Dirichlet boundary

Dirichlet boundary对方程贡献只是方程右边的一个源项，因此这个边界不改变系数矩阵的对角线

**`**div`算符**：
$$
\begin{aligned}
\phi_b&= FluxCb\,\phi_c+FluxVb \\
&= valueInternalCoeffs\,\phi_c+valueBoundaryCoeffs \\
&=0\phi_c+\phi_{specified}
\end{aligned}
$$
**`laplacian`算符**

边界面上的gradient是基于Dirichlet的值，这种情况下要再次设施边界面处的gradient，（通过梯度线性化）
$$
\begin{aligned}
\nabla \phi_b&=gradientInternalCoeffs\, \phi_c+GradientBoundaryCoeffs\ \\
&=\frac{-\phi_c+\phi_b}{d}=(-\phi_c+\phi_b)delta=-delta\, \phi_c+delta\,\phi_b
\end{aligned}
$$

## OpenFOAM 场（field）的操作和运算

### 几个常见的类：

```cpp
volScalarField
volVectorField
surfaceScalarField
surfaceVectorField
```

其实它们都是别名，定义如下：

```cpp
typedef GeometricField<scalar, fvPatchField, volMesh> volScalarField;
typedef GeometricField<vector, fvPatchField, volMesh> volVectorField;
typedef GeometricField<scalar, fvsPatchField, surfaceMesh> surfaceScalarField;//src/finiteVolume/fields/surfaceFields/surfaceFieldsFwd.H
typedef GeometricField<vector, fvsPatchField, surfaceMesh> surfaceVectorField;
```

发现，它们实际上都是 `GeometricField`，不过是提供的模板不同。首先我们看到它需要三个模板：`<Type,PatchField,GeoMesh>`。结合 `volScalarField` 和 `surfaceScalarField` 的定义，我们不难发现：第一个 `Type `可以是` scalar` `vecto`r 等，第二个` PatchField `可以是 `fvPatchField` `fvsPatchField`（**这里的 s 表示 surface**）等，第三个 `GeoMesh` 可以是` volMesh` `surfaceMesh` 等。

- `GeometricField`–**场 + 网格**，包含**内部场及其边界场**，边界场是场的场（FieldField）
- `DimensionedField`–带单位的场，**只有内部场，没有边界场**
- `Field`–数组（即 List）+ 代数操作

### field相关类的用法

**field类对象的两种构造**

```cpp
volScalarField A_
(
    IOobject
    (
        "A", //字典名字
        mesh.time().timeName(), //字典位置
        mesh, //字典注册对象
        IOobject::MUST_READ, // MUST_READ_IF_MODIFIED  NO_READ READ_IF_PRESENT
        IOobject::AUTO_WRITE // NO_WRITE
        true //默认是注册
    ),
    mesh
)

volScalarField B_                         
(
    IOobject
    (
        "B",
        mesh.time().timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("B", dimensionSet(1, -3, -1, 0, 0, 0, 0), 0.)  
    // 中间的量纲还可以这样：dimless，或者 dimMass/dimVolume
)
```

上述两种构造函数对应 `GeometricField` 源代码中的：

`````cpp
GeometricField(const IOobject&,const Mesh&);
GeometricField(const IOobject&,const Mesh&,const dimensioned<Type>&,const word& patchFieldType=PatchField<Type>::calculatedType());
`````

第一种是从文件中读取，**内部场和边界场的初始值都由文件给定，边界条件也由文件给定**。

第二种不需要从文件中读取，**内部场和边界场的初始值都是这里给定**的 0，**边界条件默认是 calculated。也可以指定边界条件类型**，如：

```cpp
volScalarField C_                         
(
    IOobject
    (
        "C",
        mesh.time().timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("C", dimensionSet(1, -3, -1, 0, 0, 0, 0), 0.),
    zeroGradientFvPatchScalarField::typeName
)
```

### **场数据的读取**

**const:**
`Internal& internalField()`, 								有量纲的内部场
`Internal::FieldType& primitiveField()`, 		 无量纲的内部场
`Boundary& boundaryField()`, 								无量纲的边界场

**non-const:**
`ref()`, 																	   有量纲的内部场
`primitiveFieldRef()`, 											无量纲的内部场
`boundaryFieldRef()`, 											  无量纲的边界场

用 `forAll `来遍历的时候，遍历的其实就是那个 `field`。
所以总体是有量纲的，用 `forAll` 对每个 `cell` 或` face` 遍历的时候，就失去量纲了。

使用举例：

```cpp
Info<<"T="<<thermo.T()<<endl; // 有量纲的 内部+边界
Info<<"T.internalField()="<<thermo.T().internalField()<<endl; // 有量纲的 内部+边界
Info<<"T.primitiveField()="<<thermo.T().primitiveField()<<endl; // 无量纲的 内部
Info<<"T.boundaryField()="<<thermo.T().boundaryField()<<endl; // 无量纲的 边界
Info<<"T.ref()="<<thermo.T().ref()<<endl; // 有量纲的 内部+边界
Info<<"T.primitiveFieldRef()="<<thermo.T().primitiveFieldRef()<<endl; // 无量纲的 内部
Info<<"T.boundaryFieldRef()="<<thermo.T().boundaryFieldRef()<<endl; //无量纲的 边界
```

### 场的**操作和运算**

#### DimensionedField中定义的函数

- 平均

```cpp
p.average() = gAverage(p)
```

- 加权平均

```cpp
p.weightedAverage(weightField) = gSum(weightField*p)/gSum(weightField)
```

​	使用举例：

```cpp
Info<<"average p is "<<p.weightedAverage(mesh.V()).value()<<endl;  
//全场压力的体积加权平均值
```

- 更改量纲 `dimensions()`

​	使用举例：

```cpp
Z_.dimensions().reset(dimless);
```

#### GeometricField 中定义的函数

- `max(), min()`
  取最大值，包括内部场和边界场。并行计算时，Info 输出的是 master 的
  使用举例：

```c++
Info<<"T=== "<<max(thermo.T())<<endl;
```

- `writeMinMax()`
  **输出最小最大值**，只包括内部场。

```c++
template<class Type, template<class> class PatchField, class GeoMesh>
void Foam::GeometricField<Type, PatchField, GeoMesh>::writeMinMax
(
    Ostream& os
) const
{
    os  << "min/max(" << this->name() << ") = "
        << Foam::min(this).value() << ", "
        << Foam::max(this).value()
        << endl;
}
```

使用举例：

```cpp
Z_.writeMinMax(Info);
```

下面是详细的测试：

T 文件：

```c++
dimensions [0 0 0 1 0 0 0];

internalField uniform 900;

boundaryField
{
    walls
    { 
        type fixedValue;
        value uniform 1800;
    }
}
```

使用举例：

```cpp
Info<<"max(T)=== "<<max(thermo.T())<<endl; //内部+边界
Info<<"min(T)=== "<<min(thermo.T())<<endl; //内部+边界
Info<<"max(T.internalField)=== "<<max(thermo.T().internalField())<<endl; // 内部
Info<<"min(T.internalField)=== "<<min(thermo.T().internalField())<<endl; // 内部
Info<<"max(T.ref)=== "<<max(thermo.T().ref())<<endl; // 内部
Info<<"min(T.ref)=== "<<min(thermo.T().ref())<<endl; // 内部
Info<<"max(T.boundaryField)=== "<<max(thermo.T().boundaryField())<<endl; // 边界
Info<<"min(T.boundaryField)=== "<<min(thermo.T().boundaryField())<<endl; // 边界
thermo.T().writeMinMax(Info); // 内部
```

输出：

```c++
max(T)=== max(T) [0 0 0 1 0 0 0] 1800
min(T)=== min(T) [0 0 0 1 0 0 0] 900
max(T.internalField)=== max(T) [0 0 0 1 0 0 0] 900
min(T.internalField)=== min(T) [0 0 0 1 0 0 0] 900
max(T.ref)=== max(T) [0 0 0 1 0 0 0] 900
min(T.ref)=== min(T) [0 0 0 1 0 0 0] 900
max(T.boundaryField)=== 1800
min(T.boundaryField)=== 1800
min/max(T) = 900, 900
```

- `gMax()`, max 的并行版

#### FieldFunctions

 是一些底层的函数，一般用不到

#### DimensionedFieldFunctions

```cpp
pow
sqr
magSqr
mag
cmptAv
gMax
gMin
gSum
gSumMag
gAverage
+
-
外积
/
^叉乘
&点乘，内积
&& 双内积
```

#### GeometricFieldFunctions

```cpp
pow
sqr
magSqr
mag
cmptAv
gMax返回的是无量纲的？
gMin
gSum
gSumMag
gAverage
+
-
外积
/
^叉乘
&点乘，内积
&& 双内积
```

### fvc 中的操作

- `volumeIntegrate()`

​	`volumeIntegrate() `的功能是对每个网格的某个物理量，乘以其网格体积，然后形成一个新的场。

```cpp
volumeIntegrate(df) = df.mesh().V()*df.field();
```

- `domainIntegrate()`

​	`domainIntegrate()` 的功能是对某个物理量，乘以其网格体积，然后对所有网格求和。

```cpp
domainIntegrate(df) = gSum(fvc::volumeIntegrate(df));
```

​	这里的` gSum` 是对全场求和。

- 其它 fvc 中的操作

```cpp
surfaceIntegrate
surfaceSum
Su
Sp
SuSp
snGrad
reconstruct
laplacian
grad
flux
div
DDt
curl
average
cellReduce
```

### 总结

1. `Field`是最基础的域，它继承了`List`的一维数组的结构用来存储域的元素;
2. `DimensionedField`则是继承自`Field`，它在`Field`的基础上添加了和**网格**Mesh相关以及文件流`regIOobject`相关的量
3. `GeometricField`则是继承自`DimensionedField`，它又在DimensionedField的基础上添加了和**边界**相关的量以及时间戳，并建立了不同时间戳下的域之间的联系。
4. 最终通过`GeometricField`的`template`模板中的类型指定为特定类型，定义出我们平时使用的域的类型

---

## OpenFOAM 网格对象

### 1. 创建网格对象

```cpp
 #include "createMesh.H"
// createMesh.H
// ~~~~~~~~~~~~
    Foam::Info
        << "Create mesh for time = "
        << runTime.timeName() << Foam::nl << Foam::endl;
    Foam::fvMesh mesh // 创建网格对象 mesh
    (
        Foam::IOobject
        (
            Foam::fvMesh::defaultRegion,
            runTime.timeName(),
            runTime,
            Foam::IOobject::MUST_READ
        )
    );
```

### 2. 网格类对象成员函数

```cpp
const scalarField& V = mesh.V(); // 返回cell volume列表
const vectorField& C = mesh.C(); // cell center coordinate
const vectorField& Cf = mesh.Cf(); // face center coordinate
const vectorField& Sf = mesh.Sf(); // face normal
const labelUList& owner = mesh.owner(); // ！！！注意是所有内部面的owner！
const labelUList& neighbour = mesh.neighbour();// 内部面的neighbor
// 如何知道边界面的owner呢？要知道边界面是属于fvBoundaryMesh类的

```

**那如何知道边界面的owner呢？**要知道边界面是属于`fvBoundaryMesh`类的

```cpp
// loop over boundary faces, except empty boundaries
// mesh.boundary()返回的对象类类型是fvBoundaryMesh
forAll(mesh.boundary(), patchi) //这里对每个bounary patch循环，mesh.boundary()返回boundary patch的数组（大面），不包含empty类型的boundary patch。
{
    // faceCells()函数返回每个patch的每个face的owner是哪个单元
    const labelUList& pOwner = mesh.boundary()[patchi].faceCells(); 
    forAll(pOwner, facei)
    {
        Info << "Boundary patch #" << patchi
            << "'s face " << "#" << facei << "'s owner cell : "
            <<  pOwner[facei] << endl;
    }
}
```

==注意==：`mesh.boundary()`返回的对象类类型是`fvBoundaryMesh`

除了`faceCell()`函数外，还可以获取boundary patch的更多信息，比如`name()`，`start()`（该patch第一个face中在所有的face中的位置）。

fvPatch指的就是我们说的boundary patch，其Access类型的函数可以返回诸多我们感兴趣的数据

```cpp
...
         //- Return name
         const word& name() const
         {
             return polyPatch_.name();
         }
         ...
         //- Return size
         virtual label size() const
         {
             return polyPatch_.size();
         }
         ...
     // Access functions for geometrical data
         //- Return face centres
         const vectorField& Cf() const;
         //- Return neighbour cell centres
         tmp<vectorField> Cn() const;
         //- Return face area vectors
         const vectorField& Sf() const;
         ...
```

有时候在写后处理程序时希望通过boundary patch的名字找到boundary patch的编号，这可以通过fvBondaryMesh提供的`findPatchID()`函数实现，`findPatchID()`函数申明：

```cpp
//- Find patch index given a name
label findPatchID(const word& patchName) const; // 返回某个pahch 的label
```

举个例子，如果希望找到fixedWall对应的boundary patch编号：

```cpp
// find patch ID by name
Info << "Patch fixedWalls's patchID = " << mesh.boundary().findPatchID("fixedWalls") << endl;

// 输出
Patch fixedWalls's patchID = 1
```

---

## OPenFOAM时间对象

### 1. 如何查找某个头文件

**1. 在`make/option`文件夹下查看**

**2. 使用`find`命令在`$FOAM_SRC`目录按文件名查找**

```bash
$ find $FOAM_SRC -name setRootCase.H 
$ FOAM_SRC/OpenFOAM/include/setRootCase.H
$ FOAM_SRC/OpenFOAM/lnInclude/setRootCase.H # 这个文件只是第一个文件的链接（对应Windows的快捷方式）
```

**==！`lnInclude`文件夹下存的是头文件的链接 ！==**,使用`list -l`命令可以查看连接指向文件的信息

```bash
list -l --dereference # 列出符号链接指向的文件的信息，而不是符号链接本身
```

### 2. 时间对象常用成员函数

```cpp
runTime.timeName();	// 当前物理时间
const scalar dt = runTime.deltaValue();// 访问当前步的时间步长
Time.controlDict();// 可以访问system/controlDict下的参数,这个函数返回的是个对象
// 例如
// self-defined control parameter
scalar tp =  runTime.controlDict().lookupOrDefault<scalar>("testParameter", 2.0);//读取controlDict下的testParameter参数
Info << "testParameter = " << tp << endl;
label ltp =  runTime.controlDict().lookupOrDefault<label>("labelTp", 2.0);//读取controlDict下的labelTp参数
Info << "labelTp = " << ltp << endl;
```



---

## 编写自己的求解器

1. 创建一个空的求解器


  ```bash
   foamNewApp mySolver
  ```
   调用命令自动创建一个空的求解器，这样就可以创建一个路径，里面有一个叫做mySolver.C的文件，文件里有写好的文件头和主函数的框子等等。这个源文件外头还有一个Make路径，Make里面也已经有了现成的files和options 文件了。

   值得注意的是，这句命令最好在applications目录下运行，这样新生成的solver会和系统的求解器放在一个路径下，避免新手搞不定编译的问题。

2. 创建网格对象
   

  实际上是根据生成的网格创建一个 ***对象***。一般不需要自己搞，只要一句话:
   ```cpp
   #include "createMesh.H"
   ```
   这句话应该是将求解器路径下的`/constant/polyMesh`下的网格文件读入程序，编程一个对象。

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
  这一段原封不动抄进去就行。到这里是创建了一个IOdictionary的对象，叫做TransportProperties。创建的时候就用IoObject来初始化。如何初始化呢？首先从从/constant路径下的叫做"transportProperties"的文件里读入数据，这分别是IoObject里面前两行的意思。剩下的就是把这个东西注册（也就是写到）mesh上，mesh是第二步里创建出来的对象。

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

[对象注册机的写详细说明参阅资料](https://www.cfd-china.com/topic/2153/openfoam%E4%B8%AD%E7%9A%84%E6%B3%A8%E5%86%8C%E6%9C%BA%E5%88%B6%E6%98%AF%E4%BB%80%E4%B9%88%E6%84%8F%E6%80%9D?lang=zh-CN https://www.dazhuanlan.com/2019/09/30/5d9197ed9f190/ https://marinecfd.xyz/post/openfoam-object-registry/#%E6%A0%91%E7%8A%B6%E7%BB%93%E6%9E%84%E7%9A%84%E7%AE%A1%E7%90%86)

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
    #include "createTime.H"//创建时间对象runtime
    #include "createMesh.H"//创建mesh对象 后续频繁使用
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

## 三个求解器例子

### 例1：OpenFOAM>>solver>>basic>>laplacianFoam

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
 
// src » finiteVolume » cfdTools » general » include
 
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
#### Tips：

runTime是类Time的一个对象，`runTime.timeName()`其实就是当前运行到的物理时间（非稳态物理问题的时间），==你程序运行到了5.1 s，`runTime.timeName()`就会将字符串“5.1”返回给你==，OpenFOAM在对不同时刻的数据进行存取的时候就是靠着这个字符串。

`runTime.constant()`返回的就是case下那个constant文件夹的名字，这个名字可以改的，默认为constant。

OpenFOAM根据case文件夹里面的system/controlDict里面对输出的设置来确定当前时刻时候输出，如果当前时刻输出的话，`outputTime()`就为true，就输出数据了。

### 例2：OpenFOAM>>solver>>basic>>potentialFoam

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
   //只有求解区域所有的压力边界都为第二类边界条件是，上面的值才会用到。如果有第一类边界条件，压力参考值为这点边界值。对于不可压缩流动压力值为相对值，上面的参考值的大小对结果无影响。
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
### 例3：OpenFOAM>>solver>>basic>>scalarTransportFoam

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
### 例4：simpleFoam详解

https://blog.csdn.net/CloudBird07/article/details/107722019

---

## IOobject机制

**OpenFOAM中使用字典和IOobject类实现输入输出操作.一个IOobject对象在构造的时候需要六个参数：对象名称，类名称，实例路径，一个objectRegistry的引用，以及描述读写方式的参数。**

**IOobject的构造函数**

1. 从对象名称，实例路径，objectRegistry引用和读写设置来构造。

```cpp
IOobject  	
(  
    const word &   	 	name,
    const word &  		instance,
    const objectRegistry &  	registry,
    readOption  		r = NO_READ,
    writeOption  		w = NO_WRITE,
    bool  			registerObject = true
)
```
2. 从对象名称，实例路径，位置，objectRegistry引用和读写设置来构造。

```cpp
IOobject  	
(
    const word &   	 	name,
    const word &  		instance,
    const fileName &  		local,
    const objectRegistry &  	registry,
    readOption  		r = NO_READ,
    writeOption  		w = NO_WRITE,
    bool  			registerObject = true
)
```

**IOobject和字典**

字典在声明的同时可以使用IOobject进行读取。通常，一个字典的内容是设置信息时，其读设置选项会设置成MUST_READ，而写设置选项则设置为NO_WRITE以防设置信息被错误的覆盖。例如通常用来读取输运性质的transportProperties字典的定义：

 ```cpp
IOdictionary transportProperties
(
     IOobject
     (
          "transportProperties",
          runTime.constant(),
          mesh,
          IOobject::MUST_READ,
          IOobject::NO_WRITE
     )
);
 ```
本例中使用了第一种构造函数，其中：

"transportProperties" 是含有字典的文件名称。

 runTime.constant()实例路径，给出字典的位置，在本例中存在于算例的constant路径下。

 objectRegistry为mesh（前面提过==polyMesh和fvMesh都是是objectRegistry的派生类==）。

**IOobject和场**
类似于字典，对于场数据的读写设置同样也可以通过IOobject类来实现。对于各种类型的场来说，调用的语法甚至都是相同的，可以参见下面的例子。如果我们想定义一个名字叫做T的volScalarField场，并将其每个时间点计算的场数据保存下来，并放在以时间点命名的路径下，可以这样实现：

```cpp
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
```
其中：

"T" 为文件名。

runTime.timeName()实例路径，这里是告诉OpenFOAM将每个文件存在以运行时间为名称的路径下面。

mesh是所需的objectRegistry。

读/写设置选项设置为MUST_READ和AUTO_WRITE以便OpenFOAM可以读取场数据并自动保存。如果不需要读场数据，则需要将MUST_READ改为NO_READ。



## openfoam添加离心力源项

```cpp
Fcent

fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U)
      + fvm::div(rhoPhi, U)
      - fvm::laplacian(muEff, U)
      - (fvc::grad(U) & fvc::grad(muEff))
      //+ Fcent
      + (rho*((2.0*M_PI/60.0*omega_vector)^((2.0*M_PI/60.0*omega_vector)^mesh.C()))) //omega_vector[1/s] in [rad/m]
    //- fvc::div(muEff*(fvc::interpolate(dev(fvc::grad(U))) & mesh.Sf()))
    );

dimensionedVector omega_vector(twoPhaseProperties.lookup("omega_vector"));

omega_vector        omega_vector [ 0 0 -1 0 0 0 0 ] (0 0 5);
```


---
**创建field类对象有两种方式：**
1. 从文件读取
2. 直接在IOobject里面给定，包括边界



**OPenFoam里的`==`**

`==`是c＋＋优先级最小的符号，在OpenFOAM中他的功能和`－`相同。
  `-fvc::grad(p)`，显式离散，该项加入到`UEqn`中的b上，前面“－”又有一个“＝＝”负负得正

——苏军伟

**FixedGradient：就是某个量法向的梯度值**

$$g_b= \frac {S} {\|S\|} \cdot \nabla _\phi $$

**openfoam列表和场（张量链表）**
```cpp
List<type>

Field<type>

typedf Field<vector> scalarField;vectorField等等
```

## openfoam中的类继承关系：


primitiveMesh：最底层的类，只包含网格的几何信息且不包含边界信息
polyMesh：包含了网格的边界信息
fvMesh：由polyMesh派生而来

polyMesh
    |___polyBoundareMesh
                 |___polyPachList
                             |___patches

fvMesh
    |___fvBoundareMesh
                 |___fvPach 
                             |___patches


(boundary由一系列patches组成)



fvMesh：由polyMesh派生而来，加入了与有限体积法相关的离散的内容。***fvMesh被用来访问所有的网格功能***。因此离散化类与函数的交互主要是通过fvMesh和fvPatch进行的。

**内部面：polyMesh->fvMesh**
**边界面：polyBoundaryMesh->fvBoundaryMesh**

==主要是fvPatch和fvMesh类实现离散化和与函数的交互==

接下来定义可以***将场量与网格结合起来的类***  `GeometricField<type,...>`
  |
  |___volField<Type>
  |___surfaceField<type>
  |___pointFiele<type>

GeometricField<type,...>继承的属性有
GeometricField<type,...>
  |
  |___Dimensions
  |___InternalField
  |___BoundaryField

## fvm和fvc

finiteVolumeMethod，隐式离散
finiteVolumeCalculate，显示计算

离散就是将微分方程转为代数方程`AX=b`，所以只有求解的量需要离散，其余的都可作为源项不用离散直接放到代数方程组的右边

`fvm`是将该项离散为代数方程从而生成系数矩阵fvMatrix类；`fvc`是显示计算（如对某时间步的场量进行某种计算）仍返回一个对应的场量geometricField类

`AX=b`，`fvm`返回的就是系数A，fvc返回的就是源项b

fvm::xxx(u)，其中的u是需要求出来的，fvc::xxx(u)，其中的u为当前时间步的值，其返回一个场。所以，需要你要求某个场u，就用fvm。

fvc为一个名字空间，它的成员都是函数，这些函数的作用就是显式地对volScalarField,volVectorField,volTensorField进行操作，将它们映射为另一个场，例如
volVectorField dUdt = fvc::ddt(U,EI) （这里EI指示了差分格式为Euler Implicit）
volVectorField vorticity = 0.5*fvc::curl(U) （U为速度场，求旋度的一半，为涡量场）
fvm的作用是产生一个矩阵。PDEs在求解的过程中需要转化为线性代数方程组，fvm正是为了完成这个任务而设计的。至于如何装配矩阵，可结合标量输运方程的离散来思考，这过程中涉及到时间离散方案、矩阵元素寻址、内存分配、甚至方程组的求解方法。这些任务没有都交给fvm去完成，而是定义了类fvMatrixScalar和fvMatrixVector。

fvm和fvc是OpenFOAM中的两个命名空间，fvm中的函数（或称操作符）将场量离散，返回的是fvMatrix，而fvc中的函数则是显式调用，返回仍然是场量。

## openfoam中的放松、松弛

>【迭代所得值】=【松弛后的值】 = （1-α）*【旧值】+ α *【新值】,若不进行松弛，则α = 1,【迭代所得值】= 【新值】,也就是没有进行松弛操作。

两种松弛方式：

>显示松弛和隐式松弛，显性松弛直接作用于求解所得变量，隐式松弛作用于系数矩阵。

- matrix relax (equation relax)是使得计算结果更慢的趋向于真实值，但换来一个对角占优矩阵

- field relax 是使得计算结果更慢的趋向于真实值,alpha越小，迭代值的波动越小，但收敛速度降低
两个都使得计算结果更慢的趋向于真实值。

涉及到 `fvSolution` 里的`alpha`，也叫`亚松驰因子`

`UEqn.relax()` ，即使松弛因子是1，其实也会对 UEqn 的 系数矩阵进行一些调整，以使它更满足对角占优。fvSolution 里面如果没有定义松弛因子，则默认值为1。

当求解过程采用定常计算时可以在/system/fvSolution里设置松弛因子，如
```cpp
relaxationFactors
{
    fields
    {
        p                   0.3;
    }
    equations
    {
        U                   0.7;
        k                   0.7;
        epsilon             0.7;
    }
}
```

## simpleFOAM湍流相关

- `MRF`：relates to rotating framework

- `turbulence->divDevReff(U)`:返回包含涡粘性系数的拉普拉斯项fvmartic

- `turbulence->correct（）`：速度修正后，用来修正该时刻的湍流量

## cfd 中的数值耗散

差分方程是微分方程的逼近，但二者之间总有误差。误差由阶次不同，可造成解的耗散和频散，其中耗散就如给流场添加了人为的粘性一样，使得本来尖锐的突越变得平滑，分辨率降低。

截断项中偶数阶微分的存在使得解具有耗散性，奇数阶微分的存在使得解具有频散性。比如一道正弦曲线，耗散使之幅值变低，而频散使之相位和周期发生变化  

## **`transformPoints`命令**

可以缩放、旋转已生成的网格

---

OpwnFOAM语句
---

- `template<class Type>` 


openfoam中的一个类模板，用于申明不同的类，class看作是变量的类型名，该变量接受类型作为其值，把Type看作是该变量的名称。

- `tmp<Field<Type>>`

tmp为of中的一类模板，可实现调用后自动释放内存，在程序中应用广泛。

- `db()` 数据库

- `pEqn.setReference(pRefCell, pRefValue);`

前面三个求解器例子里有说

Actually when solving a Navier-Stokes problem, the pressure field is off by an additive constant. Most of the time, this constant is determined by a fixed value boundary condition. However, in some case (periodic conditions for instance) the boundary conditions are of no use to fix this constant and in order to help the convergence, the trick consists to arbitrarily set a reference value to a cell of the mesh. So usually, the value of p at a refCell is set to pRefValue (usually 0).

**This line is only used if there is no fixedValue boundary condition in the domain. You can set up the value of pRefCell and pRefValue in fvSolution.**

If you remove this line and the pressure field is no fixed somewhere, then you will face tough convergence problem.

- simpleControl.H

主要的函数为loop()函数，检查当前时间步是否满足收敛条件，如满足，返回迭代终止，否则存储当前时间步中场的数据
```cpp
bool Foam::simpleControl::loop()
{
    read();     //读取controlDict中的数据，如nNonOrthCorr_，momentumPredictor_，transonic_等

    Time& time = const_cast<Time&>(mesh_.time());

    if (initialised_)
    {
        if (criteriaSatisfied())    //满足收敛条件，局部残差，总体残差
        {
            Info<< nl << algorithmName_ << " solution converged in "
                << time.timeName() << " iterations" << nl << endl;

            // Set to finalise calculation
            time.writeAndEnd(); //Write the objects now (not at end of iteration) and end                                   the run
        }
        else
        {
            storePrevIterFields();  //把当前迭代步的场存储
        }
    }
    else
    {
        initialised_ = true;
        storePrevIterFields();
    }


    return time.loop();
}
```

- createControl.H

```cpp
 #if defined(NO_CONTROL)
 #elif defined(PISO_CONTROL)
     #include "createPisoControl.H"
 #elif defined(PIMPLE_CONTROL)
     #include "createPimpleControl.H"
 #elif defined(SIMPLE_CONTROL)
     #include "createSimpleControl.H"
 #endif
```

- 如果需要去掉某个volScalarFiled变量的量纲，可以使用命令p.dimensions().reset(dimless)，其中p为volScalarFiled类型的变量。

- Info<< "Normalising E : E/rho\n" << endl;

solidDiaplacementFoam的方程中是统一除以rho之后的，因此要对E除以rho

- 报错：
 #0 Foam::error::printStack(Foam::Ostream&)

 You encountered a program error. Upon hitting that error OpenFOAM produced a stack trace (a list of the functions that were called) which is very useful to find the location at which the problem occured. It is possible to get that stack-trace with the source files and the line numbers of the functions which might help to find out what the problem is. To do so you have to compile a debug version of OpenFOAM. (see also the segmentation fault-question above)


  **correctBoundaryConditions函数**

`correctBoundaryConditions`
这个函数的作用非常简单。比如你通过下面的代码计算速度场：

`U=Ua+Ub;`

在这种情况下并没有计算U的边界条件，因此你需要

`U.correctBoundaryConditions()`

但是如果你通过UEqn.solve()的方式计算，`solve()`函数里面自动调用了`correctBoundaryConditions`。

多相流求解器里面也一样，比如
```cpp
// Correct p_rgh for consistency with p and the updated densities
    p_rgh = p - rho*gh;
    p_rgh.correctBoundaryConditions();
```

是因为前面存在赋值 `p_rgh = p - rho*gh;`

因此，我的个人习惯是，如果是solve()出来的，不需要调用，如果是=赋值出来的，都需要correctBoundaryConditions。

#### 量纲

**[kg  m  s  K  . . .]**

## 微分算子相关

1. 重要发现 ：
   

$$(\mathbf{v\cdot\nabla})\mathbf{u=\nabla u}^T\cdot \mathbf{v=v\cdot\nabla u}$$

$\nabla\cdot(\nabla\bf U)^T=\nabla(\nabla\cdot\bf U)$

$\nabla\cdot(\mathbf{U} \mathbf{U})=\mathbf{U} \cdot \nabla \mathbf{U}+\mathbf{U} \nabla \cdot \mathbf{U}$

$
\nabla (\alpha\bf U\cdot\bf V)=\alpha\bf U\cdot\nabla\bf V+\bf V\cdot\nabla\alpha\bf U$

 $
\mathrm{tr}\left(\nabla\mathbf{U}\right)\bf I=\mathrm{tr}\left(\nabla\mathbf{U}^{\mathrm{T}}\right)\bf I=\left(\nabla\cdot\mathbf{U}\right)\bf I$

1. 对标量场而言，左梯度与右梯度相等。

$$\nabla\phi=\phi\nabla$$

2. 对矢量场而言，左梯度等于右梯度的转置

$$\nabla\bf U=(\boldsymbol{\mathbf{U}} \mathrm{\nabla})^\mathrm T$$

3. 对于三维区域$\Omega$中的向量场：向量的左右散度相等

$$\nabla\cdot\bf U=\boldsymbol{\mathbf{U}} \cdot\mathrm{\nabla}$$

4. $$\nabla f=\frac{\partial f}{\partial n}\cdot \bf n$$

5. $$\nabla \cdot(f\mathbf A) =f(\nabla \cdot \mathbf A)+\mathbf A \cdot (\nabla f)$$
**牛顿-莱布尼茨公式的高维扩展**
$$\begin{equation}
\int  \boldsymbol\nabla  f  \,\mathrm{d}{V}  = \oint f  \,\mathrm{d}{ \boldsymbol{\mathbf{s}} } 
\end{equation}$$

6. 张量与向量点积：

$$a\cdot A=A^T\cdot a$$

该公式类似于散度定理，但被积函数变为标量而不是矢量．对于一维情况，该式就是牛顿—莱布尼兹公式.

7.  $\nabla(A\cdot a)$等公式：

$$\nabla \cdot(A\cdot a)=(\nabla \cdot A)\cdot a+A:(a\nabla)$$

$$\nabla\cdot(\mathbf{f} \mathbf{g})=(\nabla \cdot \mathbf{f})\mathbf{g}+(\mathbf{f\cdot \nabla }) \mathbf{g} $$

8. 张量左右散度：

$$\nabla \cdot A^T=A\cdot \nabla$$

**分部积分的高维拓展**
1. 标量分部积分

$$\begin{equation}
\int ( \boldsymbol\nabla  f) g  \,\mathrm{d}{V}  = \oint fg  \,\mathrm{d}{ \boldsymbol{\mathbf{S}} }  - \int f ( \boldsymbol\nabla  g)  \,\mathrm{d}{V} 
\end{equation}$$

2. 矢量分部积分

$$\begin{equation}
\int f ( \boldsymbol{\nabla}\boldsymbol{\cdot}   \boldsymbol{\mathbf{A}} ) \,\mathrm{d}{V}  =  \oint f  \boldsymbol{\mathbf{A}}   \boldsymbol\cdot   \,\mathrm{d}{ \boldsymbol{\mathbf{s}} }  - \int \boldsymbol{\mathbf{A}}   \boldsymbol\cdot  ( \boldsymbol\nabla  f) \,\mathrm{d}{V} 
\end{equation}$$

$$\begin{equation}
\int_\Omega u\Delta v\mathrm{d}{V}  =  \oint_{\partial\Omega} u\frac{\partial v}{\partial n}\mathrm{d}{ S }  - \int_\Omega  \nabla u\nabla v\mathrm{d}{V} 
\end{equation}$$

**对于稳态不可压缩流动这两种写法是等价的：**
$$\nabla \cdot (\mathbf{U}\mathbf{U})=(\mathbf U\cdot\nabla)\mathbf{U}$$
$$\nabla \cdot(\nabla \mathbf{U})=\nabla\cdot(\nabla\mathbf{U}+\nabla\mathbf{U}^T)$$
因为都用到了 $\nabla\cdot\mathbf U 
=\frac{\partial u}{\partial x}+\frac{\partial v}{\partial y}+\frac{\partial w}{\partial z}=0$

## 伴随灵敏度推导

伴随变量：
$$\mathbf \theta =({u}_a ,p_a ,T_a)$$

约束函数：
$$\pmb R=(\pmb R^u,R^p,R^T)$$

增广目标函数：（这是个泛函）

$$\begin{aligned} 
L&=\pmb\Psi +\int_\Omega \pmb \theta \cdot \pmb{R} d\Omega \\
&=\pmb\Psi + \int_\Omega \pmb{u}_a \cdot\Big [\Big]d\Omega + \int_\Omega p_a \cdot\Big [\Big]d\Omega + \int_\Omega T_a \cdot{}\Big [\Big]d\Omega \
\end{aligned}$$ 











