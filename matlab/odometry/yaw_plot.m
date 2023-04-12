% エンコーダと IMU で角速度の違いをプロットする %

IMU_FILEPATH = "mini_imu";
ENC_FILEPATH = "mini_enc";

enc_filepath = ENC_FILEPATH;
imu_filepath = IMU_FILEPATH;

[x, f1, f2] = main(enc_filepath, imu_filepath);

glaph_plot([f1, f2]);

legend("enc", "imu");
xlabel("距離");
ylabel("角速度 [ rad / s ]");

hold off;

function [x, f1, f2] = main(f1_filepath, f2_filepath)
    f2 = imu_yaw(f2_filepath);
    f1 = enc_yaw(f1_filepath);
    x = 0 : 1 : length(f1);
end

function omega = enc_yaw(filepath)
    datas = readmatrix(filepath);
    tread = 0.1;
    vl = datas(:, 2);
    vr = datas(:, 3);
    omega = - (vl - vr) / tread;
    for index = 1 : length(omega) - 1
        omega(index + 1) = lpf(omega(index), omega(index + 1), 0.25);
    end
end

function omega = imu_yaw(filepath)
    datas = readmatrix(filepath);
    yaw = datas(:, 2);
    omega = yaw * pi / 180;
end

function ret = lpf(prev, ref, gamma)
    ret = prev * (gamma) + ref * (1 - gamma);
end

function glaph_plot(list)
    xrange = length(list(:, 1));
    x = 1:xrange;
    quantity = length(list(1, :));
    for index = 1:quantity
        plot(x, list(:, index))
        hold on;
    end
    xlim([min(x) max(x)]);
    ymin = min(list, [], 'all');
    ymax = max(list, [], 'all');
    lim = [(ymin * 0.95), (ymax * 1.05)];
    ylim(lim)
end





