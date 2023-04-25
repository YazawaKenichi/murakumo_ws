# A Stable Tracking Control Method for an Autonomous Mobile Robot

## ABSTRACT

 This paper proposes a stable tracking control rule for non-holonomic vehicles. Stability of the rule is proved through the use of a Liapunov function. Input to the vehicle are a reference posture $(x_r,y_r,\theta_r)'$ and reference velocities $(v_r, \omega_r)'$. The major objective of this paper is to propose a control rule to find a reasonable target linear and rotational velocities $(v, \omega)'$. Linearizing the system's differential equation is useful to decide parameters for critical dumping for a small disturbance. In order to avoid any slippage, a velocity/acceleration limitation scheme was introduced. Several simulation results are presented with or without the velocity/acceleration limiter. The control rule and limiting method proposed in this paper are robot-independent and hence can be applied to various kind of mobile robots with a dead reckoning ability. This method was implemented on the autonomous mobile robot Yamabico-11. Experimental results obtained are close to the results with the velocity/acceleration limiter.

## Introduction
 The purpose of this paper is to propose a stable tracking control method for a non-holonomic vehicle with abundant simulation results. Real experimental results on the autonomous mobile robot Yamabico-11 are also presented.
 Tsudanuma proposed a method in which the reference point sequence is stored in memory. In each cycle of the locomotion control, the reference point and the future position of the robot is compared for determining the next steering [2]. Kanayama proposed a method using straight line reference for the robot's locomotion instead of a sequence of points [3]. Its velocity and steering control method has some similarities to the one proposed in this paper. Crowley developed a locomotion control system whose organization has a three layered structure [4]. He defines the concept of "virtual vehicle" which is useful for constructiong a system which is robot independent. In its command system, independent control of liner and rotational motion is possible, thus enabling smooth clothoid curves [5]. Singh used an inverse kinematic and a quintic polynomical method for compensating errors in vehicle tracking [6]. In the second method, he interpolates the current point and a future reference point with a smooth curve.
 Kanayama proposed the use of a reference and current postures for vehicle control, the use of a local error coordinate system, and a PI control algorithm for linear/rotational velocity rules in an earlier locomotion control method on the Yamabico-11 robot [7]. Nelson proposed a locomotion control method for a cart with a front steering wheel, in which they also used the error coordinate system [8]. They adopted a linear function in control rules for steering and linear velocity. These two papers are regarded as pioneers of this paper.
 In this paper, a new control rule for determining vehicle's linear and rotational velocities are given, which are different from both of [7] and [9]. The stability of the control rule is proven using a Liapunov function [9][10][11]. The use of the trace function $(1 - \cos{\theta})$ of orientation $\theta$ is successful in finding an appropriate Liapunov function [11]. One of the difficulties of this problem lies in the fact that ordinary vehicles possess only two degrees of freedom (linear velocity $v$ and rotational velocity $\omega$) for locomotion control, although vehicles have three degrees of freedom, $x$, $y$, and $\theta$ in its positioning. Another difficulty is in the non-linearity of the kinematic relation between $(v, \omega)'$ and $(\dot{x}, \dot{y}, \dot{\theta})'$. The use of a Liapunov function resolves these difficulties.
 By linearizing the system's differential equation, we find a condition for critical dumping, which gives appropriate parameters for specific control rules. The need of velocity/acceleration limitation is also discussed. After these analyses and discussions, abundant simulation results are presented. The method described so far is hardware independent and applicable to ordinary (not ommi-directional) vehicles.
 This method is useful to the class of autonomous vehicles in which (a) a dead reckning capability is provided, (b) reference path specification and current position estimation (through dead reckoning) are given separately, and (c) high precision in positional control is mandatory. This method was implemented on the autonomous mobile robot Yamabico-11 which has been developed at the University of Tsukuba, the University of California at Santa Barbara, and Naval Postgraduate School. It was demonstrated that these algorithms are sound and provided precise tracking control. An extensive set of the experimental results are shown.

## Problem Statements
 Before stating the problem, we will give a few preliminary definitions.
### Path Representation and Vehicle Kinematics
 There is a mobile robot which is located on a 2D plane in which a global Cartesian coordinate system is defined. The robot in the world possesses three degrees of freedom in its positioning which are represented by a posture,

 $p \approx \begin{bmatrix}x\\y\\z\end{bmatrix}$

where the heading direction $\theta$ is token counterclockwise from the x-axis. Let 0 denote a *null posture* $(0, 0, 2n\pi)'$, where *n* is an integer. Since the robot has a locomotion capability in the plane, the posture **p** is in fact a function of time t. The entire locus of the point $(x(t), y(t))$ is called a *path* or *trajectory*. If the time derivatives $\dot{x}$ and $\dot{y}$ exist, $\theta(t)$ is not an independent variable any more, because

$\theta(t) = tan^{-1}(\frac{\dot{y}(t)}{\dot{x}(t)})$

 The vehicle's motion is controlled by its linear velocity *v* and *rotational velocity* $\omega$, which are also functions of time. The vehicle's kinematics is defined by a Jacobian matrix *J*:

 $
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
 $

 where $\textbf{q} = (v, \omega)'$. This kinematics is common to all kinds of vehicles which are not omni-directional. (For instance, an automobile, a bicycle, a vehicle with two parallel independent power wheels - power wheeled steering system, and a tricycle) The linear velocity *v* and rotational velocity to of this kind of vehicle is controlled by its accelerator and steering wheel or handle respectively.

 ### Error Posture
 In this control sytem, two postures are used: the *reference posture* $\textbf{p}_r = (x_r, y_r, \theta_r)'$ and the *current posture $p_c = (x_c, y_c, \theta_c)'$. A reference posture is a goal posture of the vehicle and a current posture is its "real" posture at this moment respectively (Fig. 1). We will define an error posture $\textbf{p}_c$ of the two, which is a transformation of the reference posture $\textbf{p}_r$ in a local coordinate system with an origin of $(x_c, y_c)$ and an X-axis in the direction of $\theta_c$ (Fig. 2). This is the "difference" between $\textbf{p}_r$ and $\textbf{p}_c$:

$\textbf{p}_e = \begin{bmatrix} x_e \\ y_e \\ \theta_e \end{bmatrix} = \begin{bmatrix} \cos{\theta_c} && \sin{\theta_c} && 0 \\ -\sin{\theta_c} && -\cos{\theta_c} && 0 \\ 0 && 0 && 1\end{bmatrix} (\textbf{p}_r - \textbf{p}_c) \equiv T_e(\textbf{p}_r - \textbf{p}_c)$

If $\textbf{p}_r = \textbf{p}_c$, the error posture $\textbf{p}_c = 0$. If $\textbf{p}_r$ is ahead of $\textbf{p}_c$ (the vehicle is behind of the goal), $x_c > 0$. For instance, if $\textbf{p}_c = (3/2, 1, \pi/6)$ and $\textbf{p}_r = (5/2, 1+\sqrt{3}, \pi/4)$, $\textbf{p}_c = (\sqrt{3}, 1, \pi/12)$ (Figure 2 illustrates this case)

### Problem
 Now, we are able to state the architecture of a tracking control system for the vehicle (Fig.3). The global input of the system is the reference posture $\textbf{p}_r$ and *reference velocities* $\textbf{q}_r = (v_r, \omega_r)'$, which are variables of time. The global output of the system is the current posture $\textbf{p}_c$. The purpose of this tracking controller is to converge the error posture to **0**. Let us describe each component in Figure 3 fron left to right. The first component calculate an error posture from $\textbf{p}_r$ and $\textbf{p}_c$ using Equation (4). The second box is a control rule for the vehicle, which calculates a *target velocities* $\textbf{q} = (v, \omega)'$ using the error posture $\textbf{q}_c$ and the reference velocities $\textbf{q}_r = (v_r, \omega_r)$:

 $\textbf{q} = \begin{bmatrix} v \\ \omega \end{bmatrix} = \begin{bmatrix} v(\textbf{p}_e, \textbf{q}_r) \\ \omega(\textbf{q}_e, \textbf{q}_r)\end{bmatrix}$

 The third box *T* stands for the vehicle hardware capability of transforming target velocities to vehicle's real current velocities, In Sections 3 and 4, specifically, we assume the identity transformation:

 $\textbf{q}_c = \begin{bmatrix} v_c \\ \omega_c \end{bmatrix} = \begin{bmatrix} v \\ \omega \end{bmatrix} = \textbf{q}$

This *project velocity tracking assumption* simplifies the forthcoming analysis.

 The fourth box is the kinematics matrix *M* in Equation (3) to prduce the derivative of a current posture $\textbf{p}_c$. The last box is for integration. Thus, only unknown component in this system is the control rule. Since the system's input $\textbf{p}_r$ is time-variable, it is called "non-autonomous" by the definition in the control theory [9].

# A Control Scheme and Its Stability

In this section, we will find a stable control rule using a Liapunov function [9]. The following lemma follows the system depicted in Figure 1.

 *Lemma 1*

$\begin{bmatrix} \dot{x}_c \\ \dot{y}_c \\ \dot{\theta}_c\end{bmatrix} = \dot{\textbf{p}}_c = \textbf{f}(t, \textbf{p}_c) = 
\begin{bmatrix}
\omega(\textbf{p}_c, \textbf{q}_r)y_c - v(\textbf{p}_c, \textbf{q}_r) + v_r \cos{\theta}_c \\
-\omega(\textbf{p}_c, \textbf{q}_r) x_c + v_r \sin{\theta_c}
\omega_r - \omega (\textbf{p}_c, \textbf{q}_r) \\ \omega_r - \omega (\textbf{p}_e, \textbf{q}_r)\end{bmatrix}$

*Proof*. Using Equation (4) and an equality $\dot{x}_r \sin{\theta_r} = \dot{y}_r \cos{\theta_r}$ from Equation (3),

$
\dot{x}_e = (\dot{x}_r - \dot{x}_c)\cos{\theta_c} + (\dot{y}_r - \dot{y}_c)\sin{\theta_c} - (x_r - x_c)\dot{\theta}_c\sin{\theta_c} + (yr - yc)\dot{\theta}_c\cos{\theta_c} \\
= y_e \omega_c - v_c + \dot{x}_r \cos{\theta_c} + \dot{y}_r \sin{\theta_c}\\
= y_e \omega_c - v_c + \dot{x}_r \cos{\theta_r - \theta_e} + \dot{y}_r \sin{\theta_r - \theta_e}\\
= y_e \omega_c - v_c + \dot{x}_r (\cos{\theta_r}\cos{\theta_e} + \sin{\theta_r}\sin{\theta_e}) + \dot{y}_r (\sin{\theta_r} \cos{\theta_e} - \cos{\theta_r} \sin{\theta_e})\\
= y_e \omega_c - v_c + (\dot{x}_r \cos{\theta_r} + \dot{y}_r \sin{\theta_r}) \cos{\theta_e} + (\dot{x}_r \sin{\theta_r} - \dot{y}_r \cos{\theta_r}) \sin{\theta_e}
= ye \omega_c - v_c + v_r \cos{\theta_e}
$

<br>

$
\dot{y}_e = - (\dot{x}_r - \dot{x}_c)\sin{\theta_c} + (\dot{y}_r - \dot{y}_c)\cos{\theta_c} - (x_r - x_c)\dot{\theta}_c\cos{\theta_c} - (yr - yc)\dot{\theta}_c\sin{\theta_c} \\
= - x_e \omega_c + \dot{x}_r \sin{\theta_c} - \dot{y}_c \cos{\theta_c} - \dot{x}_r \sin{\theta_c} + \dot{y}_r \cos{\theta_c}\\
= - x_e \omega_c - \dot{x}_r \sin{\theta_r - \theta_e} + \dot{y}_r \cos{\theta_r - \theta_e}\\
= - x_e \omega_c - \dot{x}_r (\sin{\theta_r}\cos{\theta_e} - \cos{\theta_r}\sin{\theta_e}) + \dot{y}_r (\cos{\theta_r} \cos{\theta_e} + \sin{\theta_r} \sin{\theta_e})\\
= - x_e \omega_c + (\dot{x}_r \cos{\theta_r} + \dot{y}_r \sin{\theta_r}) \sin{\theta_e} + (\dot{x}_r \cos{\theta_r} - \dot{y}_r \sin{\theta_r}) \sin{\theta_e}
= - x_e \omega_c + v_r \sin{\theta_e}
$

