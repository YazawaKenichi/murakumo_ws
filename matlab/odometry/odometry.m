% エンコーダと IMU で自分の位置を記憶する %

FILEPATH = "mini_enc";
IMU_FILEPATH = "mini_imu";

filepath = FILEPATH;

% enc %
imu_filepath = "";
[x, y, q] = main(filepath, imu_filepath);
% glaph_plot(x, y);

% imu %
imu_filepath = IMU_FILEPATH;
[x, y, q] = main(filepath, imu_filepath);
glaph_plot(x, y);

legend("enc", "imu", "nan", "nan"); %
xlabel("x [ m ]");
ylabel("y [ m ]");

hold off;

function P_t = f(P_t_1, u_t, Dt)
    x_t_1 = P_t_1(1);
    y_t_1 = P_t_1(2);
    t_t_1 = P_t_1(3);
    v_t = u_t(1);
    w_t = u_t(2);
    if abs(w_t) < 1e-10
        x_t = x_t_1 + v_t * cos(t_t_1) * Dt;
        y_t = y_t_1 + v_t * sin(t_t_1) * Dt;
        t_t = t_t_1 + w_t * Dt;
    else
        x_t = x_t_1 + v_t * power(w_t, -1) * (   sin(t_t_1 + w_t * Dt) -  sin(t_t_1) );
        y_t = y_t_1 + v_t * power(w_t, -1) * ( - cos(t_t_1 + w_t * Dt) +  cos(t_t_1) );
        t_t = t_t_1 + w_t * Dt;
    end
    P_t = [x_t, y_t, t_t];
end

function [x, y, theta] = main(filename, imu_filename)
    use_imu = 1;
    if imu_filename == ""
        use_imu = 0;
    end
    % ファイルから左足の速度と右足の速度を取得 %
    datas = readmatrix(filename);
    datas(:, 1);
    % 結果保存変数 %
    x = zeros([length(datas(:, 1)) 1]);
    y = zeros([length(datas(:, 1)) 1]);
    theta = zeros([length(x) 1]);
    P = [x, y, theta];
    % 速度指令値のリスト %
    vl = datas(:, 2);
    vr = datas(:, 3);
    v = (vl + vr) / 2;
    % 計算周期を入力 %
    Dt = 1;
    % omega の配列を計算 %
    if use_imu
        imu_datas = readmatrix(imu_filename);
        w = imu_datas(:, 2) * pi / 180
    else
        tread = 0.1;    % 単位 [ m ] %
        w = - (vl - vr) / tread;    % 単位 [ rad / s = ( m / s ) / m ] %
        % ローパスフィルタを通す
        for k = 2 : length(w)
            w(k) = lpf(w(k - 1), w(k), 0.25);
        end
        w;
    end
    % 指令値行列 %
    u = [v, w];
    % オドメトリ配列の計算 %
    for t = 2:length(x)
        %%% オドメトリの計算 %%%
        P(t, :) = f(P(t - 1, :), u(t, :), Dt);

        %%% 値の保存 %%%
        x(t) = P(t, 1);
        y(t) = P(t, 2);
        theta(t) = P(t, 3);
    end
end

function ret = lpf(prev, ref, gamma)
    ret = prev * (gamma) + ref * (1 - gamma);
end

function glaph_plot(x, y)
    plot(x, y)

    hold on

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

    disp("plot ... OK");
end

