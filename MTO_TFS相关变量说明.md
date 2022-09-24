# MTO_TFS相关变量说明



## CostFunction


$$
\begin{align}

&\rm area = |\Omega| \\
&\text {Energy}=\frac12\cdot\frac 12(\nabla \bf U+\nabla \bf U ^T):\bf \sigma\\
&\rm C=\frac{\int Energy\ d\Omega }{C0} \\
&\rm MeanT=\frac{\int T\ d\Omega}{area} \\
&\rm V=\frac{\int x\ d\Omega}{area}-\bar V\\
&\rm powerDiss=\frac{-\int(p+\frac12 {u\cdot u})u\cdot nd\Gamma}{powerDiss0}\\


\end{align}
$$

==**注意：**==程序输出的**C**、**powerDiss**、**V**也是上面的表达式！

## sensitivity

$$
\begin{align}

&\rm gx[0]=\frac{PowerDiss}{max\{PowerDissRelax-0.2*opt\}}-1.0\\
&\rm gx[1]=\frac{C}{max\{CRelax-0.2*opt,CMax\}}-1.0\\
&\rm gx[2]=V

\end{align}
$$

## 数学模型


$$
\begin{align}
&min \ \Psi=\frac 1{|\Omega|}\int T\,d\Omega\\

&s.t. \ 
\begin{cases}

\frac1{|\Omega|}\int x\ d\Omega-\bar V \le 0\\
J-\bar J\le0\left(\frac J{\bar J}-1\le 0\right)\\
C-\bar C\le 0\left(\frac C{\bar C}-1\le 0\right)

\end{cases}


\end{align}
$$


说明：C0，powerDiss0是直管模型的上限:
$$
\rm \bar C=CMax*C0\\
\rm \bar J=PowerDissMax*Powerdiss0
$$
