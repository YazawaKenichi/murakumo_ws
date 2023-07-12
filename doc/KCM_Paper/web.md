# Kanayama Control Method
# 概要
Kanayama Control Method を用いた軌道追従についてのメモ

# 参考
- [独立２輪車型のロボットに KANAYAMA CONTROL METHOD を実装して軌道追従する](https://blog.oino.li/posts/kanayamacontrolmethod/)

# 背景

# 理論
Kanayama Control Method では現在速度・角速度と、現在位置・姿勢と本来出すべき理想的な速度・角速度を与えることで、出力すべき速度と角速度が求められる式が提案されている。

その数式が以下の数式である。

$$
\begin{equation}
q = \begin{bmatrix} v \\ \omega \\ \end{bmatrix} = \begin{bmatrix}v(p_e, q_r)\\ \omega(p_e, q_r)\end{bmatrix}=\begin{bmatrix}v_r\cos{\theta_e}+K_xx_e\\ \omega_r + v_r(K_yy_e+K_\theta\sin{\theta_e})\end{bmatrix}
\end{equation}
$$
