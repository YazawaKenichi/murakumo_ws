% 指定された軌道を追従する %
% どうやってロボットが軌道から外れるのを再現しようってんだい？ %

ENC_REFERENCE = "desk_enc"
IMU_REFERENCE = "desk_imu"

enc_datas = readmatrix(ENC_REFERENCE);
imu_datas = readmatrix(IMU_REFERENCE);

x = zeros([length(datas(:, 1)) 1]);
y = zeros([length(datas(:, 1)) 1]);
theta = zeros([length(datas(:, 1)) 1]);

for index = 1:length(length(enc_datas(:, 1)) 1]);
encl = enc_datas(index, 2);
encr = enc_datas(index, 3);

yaw = imu_datas(index, 2) * pi / 180;

theta_c += omega_now;
theta_r += yaw[i];
theta_e = theta_c - theta_r;


