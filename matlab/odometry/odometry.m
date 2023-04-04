% エンコーダの回転数だけでオドメトリを取る %

FILEPATH = "desk_enc";
IMU_FILEPATH = "desk_imu";

filepath = FILEPATH;
imu_filepath = IMU_FILEPATH;

[x, y] = main(filepath, imu_filepath);

glaph_plot(x, y);
% legend("imu", "nan", "nan", "nan"); %
xlabel("x [ m ]");
ylabel("y [ m ]");
hold off;

function [x, y] = main(filename, imu_filename)

    use_imu = 1;
    if imu_filename == ""
        use_imu = 0;
    end

    % ファイルから左足の速度と右足の速度を取得 %
    datas = readmatrix(filename);
    datas(:, 1);
    x = zeros([length(datas(:, 1)) 1]);
    y = zeros([length(datas(:, 1)) 1]);
    theta = zeros([length(x) 1]);
    % 計算周期を入力 %
    sampling_time = 1;
    for index = 1:length(x) - 1
        vl = datas(index, 2);
        vr = datas(index, 3);
        v = (vl + vr) / 2;
        omega = 0;
        if use_imu
            imu_datas = readmatrix(imu_filename);
            omega = imu_datas(index, 2) * pi / 180;
        else
            tread = 0.1;    % 単位 [ m ] %
            omega = (vl - vr) / tread;    % 単位 [ rad / s = ( m / s ) / m ] %
        end
        theta(index + 1) = theta(index) + omega * sampling_time;
        % 現在速度と現在角度から二次元座標上の x-y 速度を出す %
        vx = v * cos(theta(index + 1));
        vy = v * sin(theta(index + 1));
        % 積分する %
        x(index + 1) = x(index) + vx * sampling_time;
        y(index + 1) = y(index) + vy * sampling_time;
    end
end

function glaph_plot(x, y)
    hold off;
    plot(x, y)
    hold on;

    % 最大値と最小値の取得 %
    xmin = min(x);
    ymin = min(y);
    xmax = max(x);
    ymax = max(y);

    % 中央の座標を取得する %
    xc = (xmin + xmax) / 2;
    yc = (ymin + ymax) / 2;

    % 縦横の長さを計算する %
    xrange = xmax - xmin;
    yrange = ymax - ymin;

    padding = 1.2;

    % 長い方で正方形を作る %
    half_range = padding * max(xrange, yrange) / 2;

    % プロットの領域を設定する %
    xlim([xc - half_range, xc + half_range]);
    ylim([yc - half_range, yc + half_range]);

    disp("plot ... OK")
end

