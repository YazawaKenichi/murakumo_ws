# Kanayama Control Method

## 速度を追従させる
velotrace_set_target_direct(float target);

## 角度を追従させる
angletrace_set_target_direct(float target);

# 注意
angle 方向の追従値の更新をしてないよ！

## KCM の実装
一定周期で実行
``` c++
//! オドメトリの更新
odometry_update()
//! 現在の速度と角速度を取得
q_n = localization_get_twist();
//! 現在の位置を取得
p_c = localization_get_pose();
//! 出力すべき（角）速度を計算
q = kcm_sample(q_n, p_c);
```
