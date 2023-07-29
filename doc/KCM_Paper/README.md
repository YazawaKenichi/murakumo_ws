# A Stable Tracking Control Method for an Autonomous Mobile Robot

## ABSTRACT

この論文は「[非ホロノミック車両](http://www.iis.u-tokyo.ac.jp/~suzukitk/research-nh-j.html)のための安定追従制御の方法」を提案する。ルールの[安定性はリアプノフ関数によって証明された](https://math-fun.net/20190709/1954/)。(非ホロノミック型の)車両への入力は基準姿勢と基準速度である。この論文の主な目的は「合理的なターゲットの直線速度と回転速度を見つける制御方法」を提案することです。

## 1. Introduction

この論文の目的は、豊富なシミュレーションの結果から、非ホロノミックのための安定追従制御方式を提案することです。ツムラの提案した基準点シークエンスのうちの方法は、メモリにストアされる。移動の各サイクルで、ロボットの基準点と将来の位置は次のステアリングを決定するために比較される。カナヤマはロボットの移動に点列の代わりに直線参照を使用する方法を提案した。

## 2. Problem Statements

問題を説明する前に、いくつかの予備的な定義を示す。

### 2.1. Path Representation and Vehicle Kinematics

グローバルデカルト座標系が定義されている 2D 平面上に配置された移動ロボットがある。この世界のロボットは、姿勢によって表現される配置に、３つの自由度を持つ。

$$
\begin{equation}
\textbf{p} = \begin{bmatrix} x \\ y \\ \theta \end{bmatrix}
\end{equation}
$$

ここで、ヘディング方向 theta は x 軸から反時計回りの記号。n を整数とし、(0, 0, 2nPI)' でゼロ姿勢とする。ロボットは平面内での移動能力を備えているため、姿勢 p は実際には時間 t の関数。点 (x(t), y(t)) の軌道全体をパス path または軌跡 trajectory と呼ぶ。時間導関数 $\dot{x}(t)$ と $\dot{y}(t)$ が存在する場合

$$
\begin{equation}
\theta(t) = \tan^{-1}(\frac{\dot{y}(t)}{\dot{x}(t)})
\end{equation}
$$

であるため、$\theta(t)$ はもはや独立変数ではない。(dotx と doty で表せてしまう) 車両の運動は、時間の関数でもある線速度 v と回転速度 $\omega$ によって制御される。車両の運動学はヤコビ行列 J :

$$
\begin{equation}
\begin{bmatrix}
\dot{x}\\
\dot{y}\\
\dot{\theta}\\
\end{bmatrix}
= \dot{p} = J\textbf{q} \equiv \begin{bmatrix}
\cos\theta && 0 \\
\sin\theta && 0 \\
0 && 1
\end{bmatrix}\textbf{q}
\end{equation}
$$

$$\textbf{q} = (v, \omega)'$$

この運動学は、全方向性ではないすべての種類の車両 ( 自動車・自転車・対向二輪・ステアリング・三輪車 など ) に共通。v は接線速度で $\omega$ は回転速度。

### 2.2 Error Posture

この制御システムでは、2 つの姿勢が使用されます。 基準姿勢 (reference posture) $p_r = (x_r, y_r, \theta_r)'$、現在姿勢 $p_c = (x_c, y_c, \theta_c)'$。 基準姿勢 (reference posture) は車両の目標姿勢 (goal posture) であり、現在姿勢は現時点での「実際の」姿勢です (図 1)。 2 つの誤差姿勢 $p_e$ を定義します。これは、目標姿勢 $p_r$ を、原点 $(x_c, y_c)$ と $\theta_c$ 方向の X 軸を持つローカル座標系に変換したものです (図 1)。 2)。 これが $p_r$ と $p_c$ の「差」：

$$
\begin{equation}
\textbf{p}_e = \begin{bmatrix} x_e \\ y_e \\ \theta_e \end{bmatrix} = \begin{bmatrix} \cos{\theta_c} && \sin{\theta_c} && 0 \\ -\sin{\theta_c} && -\cos{\theta_c} && 0 \\ 0 && 0 && 1\end{bmatrix} (\textbf{p}_r - \textbf{p}_c) \equiv T_e(\textbf{p}_r - \textbf{p}_c)
\end{equation}
$$

$p_r = p_c$ の場合、エラー姿勢 $p_e$。 $p_r$ が $p_c$ より進んでいる (vehicle がゴールの後ろにある) 場合、$x_e >0$。 たとえば、$p_c = (3/2, 1, \pi/6)$ かつ $p_r = (5/2, 1 + \sqrt{3}, \pi/4)$ の場合、$p_e = (\sqrt{3} , 1, \pi/12)$ (図 2 はこのケースを示しています)。

### 2.3. Problem

これで、車両の追跡制御システムのアーキテクチャを述べることができます (図 3)。 システムのグローバル入力は、時間の変数である基準姿勢 $p_r$ と基準速度 $q_r = (v_r, \omega_r)'$ です。 システムのグローバル出力は、現在の姿勢 $p_c$ です。 このトラッキング コントローラの目的は、誤差姿勢を 0 に収束させることです。図 3 の各コンポーネントを左から右に説明します。 最初のコンポーネントは、式 (4) を使用して、$p_r$ と $p_c$、および $p_c$ からエラー ポスチャを計算します。 2 番目のボックスは、誤差姿勢 $p_e$ と基準速度 $q_r = (v_r, \omega_r)$ を使用して目標速度 $q = (v, \omega)^t$ を計算する車両の制御規則です。

$$
\begin{equation}
\textbf{q} = \begin{bmatrix} v \\ \omega \end{bmatrix} = \begin{bmatrix} v(\textbf{p}_e, \textbf{q}_r) \\ \omega(\textbf{q}_e, \textbf{q}_r)\end{bmatrix}
\end{equation}
$$

3 番目のボックス *T* は、目標速度を車両の実際の現在の速度に変換する車両ハードウェア機能を表します。具体的には、セクション 3 と 4 では、恒等変換 ( 以下の式 ) を想定しています。

$$
\begin{equation}
\textbf{q}_c = \begin{bmatrix} v_c \\ \omega_c \end{bmatrix} = \begin{bmatrix} v \\ \omega \end{bmatrix} = \textbf{q}
\end{equation}
$$

この*プロジェクトの速度追跡の仮定*により、今後の分析が簡素化されます。

4 番目のボックスは、式 (3) の運動行列 *M* で、現在の姿勢 $\textbf{p}_c$ の導関数を生成します。 最後のボックスは統合用です。 したがって、このシステムの未知のコンポーネントのみが制御ルールです。 システムの入力 $\textbf{p}_r$ は時間変数であるため、制御理論の定義では「非自律的」と呼ばれます [9]。

## 3. A Control Scheme and Its Stability

このセクションでは、リアプノフ関数 [9] を使用して安定制御規則を見つけます。 次のレンマは、図 1 に示したシステムに従います。

*Lemma 1*

$$
\begin{equation}
\begin{bmatrix} \dot{x}_c \\ \dot{y}_c \\ \dot{\theta}_c\end{bmatrix} = \dot{\textbf{p}}_c = \textbf{f}(t, \textbf{p}_c) =
\begin{bmatrix}
\omega(\textbf{p}_c, \textbf{q}_r)y_c - v(\textbf{p}_c, \textbf{q}_r) + v_r \cos{\theta}_c \\
-\omega(\textbf{p}_c, \textbf{q}_r) x_c + v_r \sin{\theta_c}
\omega_r - \omega (\textbf{p}_c, \textbf{q}_r) \\ \omega_r - \omega (\textbf{p}_e, \textbf{q}_r)\end{bmatrix}
\end{equation}
$$

*Proof*. 式 (4) と式 (3) からの等式 $\dot{x}_r \sin{\theta_r} = \dot{y}_r \cos{\theta_r}$ を使用します。

$
\dot{x}_e = (\dot{x}_r - \dot{x}_c)\cos{\theta_c} + (\dot{y}_r - \dot{y}_c)\sin{\theta_c} - (x_r - x_c)\dot{\theta}_c\sin{\theta_c} + (yr - yc)\dot{\theta}_c\cos{\theta_c} \\
= y_e \omega_c - v_c + \dot{x}_r \cos{\theta_c} + \dot{y}_r \sin{\theta_c}\\
= y_e \omega_c - v_c + \dot{x}_r \cos{\theta_r - \theta_e} + \dot{y}_r \sin{\theta_r - \theta_e}\\
= y_e \omega_c - v_c + \dot{x}_r (\cos{\theta_r}\cos{\theta_e} + \sin{\theta_r}\sin{\theta_e}) + \dot{y}_r (\sin{\theta_r} \cos{\theta_e} - \cos{\theta_r} \sin{\theta_e})\\
= y_e \omega_c - v_c + (\dot{x}_r \cos{\theta_r} + \dot{y}_r \sin{\theta_r}) \cos{\theta_e} + (\dot{x}_r \sin{\theta_r} - \dot{y}_r \cos{\theta_r}) \sin{\theta_e}
= ye \omega_c - v_c + v_r \cos{\theta_e}
$

<br>

$$
\dot{y}_e = - (\dot{x}_r - \dot{x}_c)\sin{\theta_c} + (\dot{y}_r - \dot{y}_c)\cos{\theta_c} - (x_r - x_c)\dot{\theta}_c\cos{\theta_c} - (yr - yc)\dot{\theta}_c\sin{\theta_c} \\
= - x_e \omega_c + \dot{x}_r \sin{\theta_c} - \dot{y}_c \cos{\theta_c} - \dot{x}_r \sin{\theta_c} + \dot{y}_r \cos{\theta_c}\\
= - x_e \omega_c - \dot{x}_r \sin{\theta_r - \theta_e} + \dot{y}_r \cos{\theta_r - \theta_e}\\
= - x_e \omega_c - \dot{x}_r (\sin{\theta_r}\cos{\theta_e} - \cos{\theta_r}\sin{\theta_e}) + \dot{y}_r (\cos{\theta_r} \cos{\theta_e} + \sin{\theta_r} \sin{\theta_e})\\
= - x_e \omega_c + (\dot{x}_r \cos{\theta_r} + \dot{y}_r \sin{\theta_r}) \sin{\theta_e} + (\dot{x}_r \cos{\theta_r} - \dot{y}_r \sin{\theta_r}) \sin{\theta_e}
= - x_e \omega_c + v_r \sin{\theta_e}
$$

$v_c$ と $w_c$ をそれぞれ $v(p_e, q_r)$ と $v(p_e, q_r)$ で置き換えます (式 (6) と (5) を参照)。 補題を得る． □

次のように、ターゲット速度の制御規則 (5) の特定のインスタンスを提案します。

$$
\begin{equation}
q = \begin{bmatrix} v \\
\omega \\
\end{bmatrix} = \begin{bmatrix}v(p_e, q_r)\\
\omega(p_e, q_r)\end{bmatrix}=\begin{bmatrix}v_r\cos{\theta_e}+K_xx_e\\
\omega_r + v_r(K_yy_e+K_\theta\sin{\theta_e})\end{bmatrix}
\end{equation}
$$

ここで、 $K_x$, $K_y$ および $K_\theta$ は正の定数です。 各速度の最初の項はフィードフォワード部分です。補題 1 により:

補題２：
$$
\begin{equation}
\dot{p}_e = f(t, p_e) =
\begin{bmatrix}
(\omega_r+v_r(K_yy_e+K_\theta\sin{\theta_e}))y_e-K_xx_e\\
-(\omega_r+v_r(K_yy_e+K_\theta\sin{\theta_e}))x_e+v_r\sin{\theta_e}\\
-v_r(K_yy_e+K_\theta\sin{\theta_e})
\end{bmatrix}
\end{equation}
$$

この制御規則 (8) の健全性は、次の命題によって確立されます。

> 命題１：制御規則 (8) を使用すると、$p_e = 0$ は基準速度 $v_r > 0$ の安定平衡点となる。

証明：リアプノフ関数の候補としてスカラー関数 $V$ を提案しよう [9]：

$$
\begin{equation}
V = \frac{1}{2}(x_e^2+y_e^2)+(1-\cos{\theta_e})/K_y
\end{equation}
$$

明らかに、$V \geq 0$ です。 $p_e = 0$ の場合、$V = 0$。 $p_e \neq 0$ の場合、$V > 0$。 さらに補題 2 より:

$
\dot{V}=\dot{x}_ex_e+\dot{y}_ey_e+\dot{\theta}_e\sin{\theta_e}/K_y\\
=[(\omega_r+v_r(K_yy_e+K_\theta\sin{\theta_e}))y_e-K_xx_e]x_e\\
+[-(\omega_r+v_r(K_yy_e+K_\theta\sin{\theta_e}))x_e+v_r\sin{\theta_e}]y_e\\
+[-v_r(K_yy_e+K_\theta\sin{\theta_e})]\sin{\theta_e}/K_y\\
=-K_xx_e^2-v_rK_\theta\sin^2{\theta_e}/K_y\leq{0}
$

すると、$V$ はリアプノフ関数になります。□

次の命題は、いくつかの条件下で $p_e = 0$ 付近で一様に漸近的に安定であることを示しています。

> 命題２： (a) $v_r$ と $\omega_r$ が連続している、(b) $v_r$、$\omega_r$、$K_x$、および $K_\theta$ が有界である、(c) $\dot{v }_r$ と $\dot{\omega}_r$ は十分に小さいです。 これらの条件下では、$p_e = 0$ は $[0, \infty)$ にわたって一様に漸近的に安定しています。

証明：$p_e = 0$ の周りで微分方程式 (9) を線形化すると、次のようになります。

$$
\begin{equation}
\dot{p}_e = Ap_e
\end{equation}
$$

ここで

$$
\begin{equation}
A =
\begin{bmatrix}
-K_x&&\omega_r&&0\\
-\omega_r&&0&&v_r\\
0&&-v_rK_y&&-v_rK_\theta\\
\end{bmatrix}
\end{equation}
$$

このとき、A (.) は連続微分可能で有界です。 A の特性方程式は次のとおりです。

$$
\begin{equation}
a_3s^3+a_2s^2+a_1s+a_0=0
\end{equation}
$$

ここで

$$
\begin{equation}
\left\{
\begin{array}{l}
a_3 = 1\\
a_2 = K_\theta v_r+K_x\\
a_1 = K_yv_r^2+K_xK_\theta v_r + \omega_r^2\\
a_0 = K_xK_yv_r^2+\omega_r^2K_\theta v_r
\end{array}
\right.
\qquad{(13)'}\nonumber
\end{equation}
$$

すべての係数 $a_i$ が正で $a_1a_2-a_0a_3 > 0$ であるため、ラウス・ハーヴィッツ基準によれば、すべての根の実部は負になります。 したがって、[9] の 223 ページの系 41 により、命題は証明されました。□

## 4. Effects of Control Parameters

前のセクションでは、$K_x$、$K_y$、および $K_\theta$ のパラメーター値の任意の組み合わせに対してシステムが安定していることを実証しました。 ただし、ロボットの非振動性ではあるが、遅すぎない応答が必要なため、オプションのパラメーター セットを見つける必要があります。 解析を単純化するために、基準姿勢が $x$ 軸上で正の方向に一定速度 $V_r$ で移動している状況のみを考慮します：

$$
\begin{equation}
\begin{array}{l}
p_r(t)=\begin{bmatrix}x_r(t)\\
y_r(t)\\
\theta_r(t)\end{bmatrix}=\begin{bmatrix}V_rt\\
0\\
0
\end{bmatrix}\\
and\\
q_r(t)=\begin{bmatrix}v_r(t)\\
\omega_r(t)\end{bmatrix} = \begin{bmatrix}V_r\\
0
\end{bmatrix}
\end{array}
\end{equation}
$$

この状態は線形参照モリオンと呼ばれます。さらに、次のことを前提としています。

$$
\begin{equation}
\begin{array}{l}
|\theta_e| \ll 1\\
and\\
|\dot{\theta}_e| \ll 1
\end{array}
\end{equation}
$$

> 命題 3：条件 (14) および (15) の下で、以下の式が成立する

$$
\begin{equation}
\dot{p_c}=\begin{bmatrix}\dot{x}_c\\
\dot{y}_c\\
\dot{\theta}_c\end{bmatrix}=\begin{bmatrix}-K_x && 0 && 0\\
0 && 0 && V_r\\
0 && -V_rK_y && -V_rK_\theta
\end{bmatrix}
\begin{bmatrix}x_c-V_tt\\
y_c\\
\theta_c
\end{bmatrix}
+
\begin{bmatrix}
V_r\\
0\\
0
\end{bmatrix}
\end{equation}
$$

証明

式 (11) を式 (4) に代入すると、

$$
\begin{equation}\dot{p_c}=T_e^-1(AT_e-\dot{T_e})(p_c-p_r)+\dot{p}_r\end{equation}
$$

式 (4)、条件 (14)、(15) により、 $|\theta_c| = |\theta_e|\ll1$, $|\dot{\theta}_c|=|\dot{\theta}_e|\ll1$. したがって、式 (17) の $T_e$ と $\dot{T}_e$ は、それぞれ単位行列とヌル行列と見なすことができます。 したがって、

$$
\dot{p}_c = A(p_c - p_r)+\dot{p}_r
$$

前の式を式 (4) と条件 (14) に代入します。式（16）が得られます。□

式 (16) は、$x_c$ が $y_c$ と $\theta_c$ に依存しない振る舞いを示しています。 $1/K_x$ は指数関数的減衰の時定数に対応します。

自明 1 : $t = 0$ において $x_c = \Delta{x}$ の時、

$$
\begin{equation}
x_c = V_rt + \Delta{x}e^{-K_xt}
\end{equation}
$$

式 (16) の $\theta_e$ をキャンセルすると、

$$
\begin{equation}
\ddot{y}_c+2\zeta\xi\dot{y}_c+\xi^2=0
\end{equation}
$$

ここで,

$
\begin{array}{l}
\zeta = \frac{K_\theta}{2\sqrt{K_y}}\\
and\\
\xi = V_r\sqrt{K_y}
\end{array}
$

自明 2 : 臨界減衰の条件は

$$
\begin{equation}
K_\theta^2=4K_y
\end{equation}
$$

自明 3 :

$$
\begin{equation}
p_c = \begin{bmatrix}V_rt\\\Delta{y}(1+\xi t)e^{-\xi t}\\-\Delta{y}\xi^2te^{-\xi t}\end{bmatrix}
\end{equation}
$$

この動きでは、$x_c$ が $4/\sqrt{K_y}$ になるとき、$y_c / \Delta{y}$ の m r 比は 9.2% に減少します。

3 つの異なる収束特性に関するシミュレーション結果を図 4 に示します。ここで、ロボットの $p_r$ と $p_c$ は *x* 軸上を正の方向に移動していましたが、$y_r$ が $\Delta y = 5 cm$ で突然跳ね上がります。平行水平基準運動を続けながら。共通のパラメータは、$v_r = 30 cm/sec, Ky = 6.4 \times 10^-3 /cm, \xi = 2.4 /sec$,および $K_x = 10 /sec$ です。オーバー ダンピング ケース ($\zeta = 0.75$ および $K_\theta = 0.12/cm$), クリティカル ダンピング ケース ($\zeta = 1$ および $K_\theta = 0.16 /cm$)、および振動ケース。($\zeta = 1.25$ および $K_\theta = 0.20 /cm$) が使用されます。$\Delta y$ 摂動が 5cm と小さいため、シミュレーションと解析の結果は一致します。以下の実験と実際の実装では、臨界減衰条件 $\zeta = 1$ を採用します。これは、収束が非振動性共編集下で最も速いためです。

## 5. Velocity/Acceleration Limiting

このトラッキング コントローラ システムでは、$p_r(t)$ と $q_r(t)$ で指定される参照パスは、次の「滑らかさ」の条件 (前置詞 2) を満たす必要があります。(a) パス自体は連続、(b) パスは接線方向連続、(c) パス曲率は連続、(d) 導関数 $\dot{v}_r$ は有界、(e) 導関数は $\dot{\omega}_r$ は有界です (したがって、曲率の導関数も有界です)。この曲率連続性要件 (c) が、クロルトイド曲線、3 次螺旋、および極多項式が車両経路計画のために開発された理由です [5][13][14]。

しかし、ナビゲーターの立場からすれば、平坦ではない経路を使用できると便利です。 線分と角膜からなるパスは曲率連続性を持たないが、そのようなパスは広く使われている[7][15][16][17]。 移動ロボットやまびこ 11 号の MML 言語では、ロボットの位置誤差を動的に補償する *set-current(&p)* という関数が用意されており、リアルタイム ナビゲーション実験で頻繁に使用されます [19]。 ただし、これらの非スムーズなパスを許可すると、(i) 式 (8) による目標速度 $(v, \omega)$ のいずれかまたは両方が、実際の車両で達成するには大きすぎる可能性があり、(ii) 直線/回転加速度が大きくなりすぎて、ロボットのスリップが発生する可能性があります (スリップは推測航法の深刻なエラーの原因となります)。 したがって、これらの滑らかでない参照パスを処理するには、速度と加速度のリミッターが必要です。 目標速度 $(v, \omega)$ を定数 $(\hat{v}, \hat{w})$ で制限し、目標加速度 $(a, \alpha)$ を定数 $(\hat{a}, \hat{\alpha})$ で制限する単純なアルゴリズムを採用します。ここで $a = \dot{v}$ は *線形目標加速度*、$\alpha = \dot{\omega}$ は *回転目標加速度*。 この変更は、図 3 のボックス $T$ に実装されています。

図 5 は、速度/加速度リミッターがある場合とない場合の $\Delta y$ のさまざまな値のシミュレーション結果を示しています。 リミッターを使用すると、リミッターを使用しない場合よりも応答が遅くなることに注意してください。 以降、すべてのシミュレーションは、クリティカル ダンピング パラメータ セットを使用して実行されます。 図 6 は、$\Delta \theta$ 制限なしの不連続ジャンプ ($\Delta\theta = \pi / 4$, $\pi/2$ and $3\pi/4$) のシミュレーション結果を示しています。 図 7 は、速度/加速度の制限がある $\Delta \theta$ 不連続ジャンプのシミュレーション結果を示しています。

## 6. Implementation

セクション 3、4、および 5 で提示された結果は、ハードウェアに依存しませんでした。 このセクションでは、この理論がロボットやまびこ-11 にどのように実装されたかを説明します。

### 6.1 Determining Control Parameters

$K_x$ が大きいほど収束が速くなり、定常誤差 $x_e$ が減少します。 ただし、ロボットのハードウェアのサンプリング時間に匹敵する時定数 $1 / K_x$ を持つことは適切ではありません。 $K_x$ が大きくなると、停止状態 ($p_r = constant$) でも制御システムが振動し、不安定になる傾向があります。 定数 $1/K = 33 ms$ がロボットのサンプリング時間 $T_s = 10 ms$ と互換性がある場合、$K_x = 30 /sec$ で振動が観察されます。 これらの要因のバランスをとって、$K_x = 10 / sec$ が選択されました。

セクション 4 の臨界減衰条件 ($\zeta = 1$) を採用して、現在の姿勢 $p_c$ の適切な応答に対する $\xi$ の値も決定します。$\xi$ が大きいほど収束が速くなります。ただし、$\xi$ が大きすぎると、ロボットに過剰な回転速度が要求されます。$\Delta y$ のわずかな摂動の後、ロボットが 50cm の走行中に誤差 $y_c/\Delta y$ を 9.2% に減らすようにパラメータを調整することにしました。したがって、系 2 と 3 により、値 $K_y = 6.4 \times 10^{-3} /cm^2$ と $K_\theta = 0.16 /cm$ が決定されます。この場合、時定数 $1/\xi = 1/2.4 sec$ は、サンプリング時間 $T_s = 10 ms$ よりも十分に大きくなります。

これらの $K_x$、$K_y$、および $K_\theta$ では、振動は見られませんでした。 30 cm/秒の一定の基準速度での誤差 $x_e$ と $y_e$ は、それぞれ約 2mm と 1mm 未満です。

### 6.2 Determining Maximum Velocity/Acceleration

やまびこ11号の最大線速度は65cm/秒と知られています。ロボットが $\hat{v}$ で走行し、同時に $\hat{\omega}$ で回転している場合でも、外輪の速度がその最大速度である 65 cm/sec を超えないという条件を考慮する必要があります。したがって、

$
\hat{v}+\hat{omega}(\frac{W}{2})<65 cm/sec
$

ここで、W はトレッド (52.4cm) です。 この関係により、最大速度を $(\hat{v}, \hat{\omega}) = (40 cm/sec, 0.8 rad/sec)$ として選択しました。 $\hat{a}$ と $\hat{\alpha}$ の値は、ロボットが滑らない実験によって決定します: $(\hat{a}, \hat{\alpha}) = (50 cm/sec^2, 5 rad/sec)$.

### 6.3 Experimental Results

$K_y$ と $K_\theta$ のこれらの値が妥当であることを確認するために、いくつかの実験を行いました。 図 8 は、図 4 に対応する $\zeta$ の 3 つの異なる値を使用した実験結果を示しています。図 9 は、図 5 に対応する $\Delta y$ の結果を示しています。 図 10 は、図 7 に対応する $\Delta\theta$ の結果を示しています。 軌道は、車両の推測航法によって得られる現在の姿勢 $p_c$ を使用してプロットされます。

## Acknowledgement

著者は、ヤマビコ 11 号の設計と構築について、湯田真一博士、進藤道行、梶原貞次郎氏に感謝します。また、トラッキング コントローラを含む以前のバージョンのヤマビコ ソフトウェア システムの設計と実装について、Amir Nilipour 氏と Tony Lelm 氏に感謝します。 著者らは、安定性理論に関する有益なコメントをくださった Daniel Koditschek 博士にも感謝します。

# Point

1. 現在位置姿勢を求める ()
2. 現在位置姿勢と目標位置姿勢の差を求める (4)
3. 

