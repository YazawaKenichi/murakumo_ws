% ループを用いた積分 VS 状態遷移関数を用いた積分 %
% エンコーダ や IMU のデータから X, Y オドメトリを出力 %

FILEPATH = "mini_enc";
IMU_FILEPATH = "mini_imu";
OUT = "Data";

compare_transition_and_roop(FILEPATH, IMU_FILEPATH, OUT)

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

function [x, y, theta] = roop(filename, imu_filename)
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
        w = imu_datas(:, 2) * pi / 180;
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
    for t = 1:length(x) - 1
        %%% オドメトリの計算 %%%
        x(t + 1) = x(t) + v(t + 1) * cos(theta(t)) * Dt;
        y(t + 1) = y(t) + v(t + 1) * sin(theta(t)) * Dt;
        theta(t + 1) = theta(t) + w(t + 1);
    end
end

function [x, y, theta] = state_transition(filename, imu_filename, out)
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
        w = imu_datas(:, 2) * pi / 180;
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
    for t = 1:length(x) - 1
        %%% オドメトリの計算 %%%
        P(t + 1, :) = f(P(t, :), u(t + 1, :), Dt);

        %%% 値の保存 %%%
        x(t + 1) = P(t + 1, 1);
        y(t + 1) = P(t + 1, 2);
        theta(t + 1) = P(t + 1, 3);
    end
    tx = zeros([length(x) 1]);
    ty = zeros([length(y) 1]);
    tt = zeros([length(theta) 1]);
    for i = 1 : length(x) - 1
        tx(i + 1) = 1000 * (x(i + 1) - x(i));
        ty(i + 1) = 1000 * (y(i + 1) - y(i));
        tt(i + 1) = 1000 * (theta(i + 1) - theta(i));
    end
    tP = [tx, ty, tt];
    save_plot(tP, out)
    % save_plot(P, out) %
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

function compare_transition_and_roop(filepath, imu_filepath, out)
    [x, y, q] = roop(filepath, imu_filepath);
    glaph_plot(x, y);

    [x, y, q] = state_transition(filepath, imu_filepath, out);
    glaph_plot(x, y);

    legend("roop", "transition", "nan", "nan"); %
    xlabel("x [ m ]");
    ylabel("y [ m ]");

    hold off;
end

function save_plot(A, path)
    writematrix(A, path)
end

