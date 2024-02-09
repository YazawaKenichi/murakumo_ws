% ファイルから IMU と エンコーダの値を取得 %
% 取得した値を x(t) - x(t-1) の形で変数に格納 %
% 格納した変数を平滑化 %
% グラフとしてプロット %

IMU = "mini_imu";
ENC = "mini_enc";

adj = 5;
path = "test.csv";

[P, datas] = state_transition(ENC, IMU);
dP = differential(P);
Pr = smoothing(dP, adj);
plt(dP, Pr);
csv(path, datas, P, dP, Pr, adj);

function Pt = f(Pt1, ut, dt)
    xt1 = Pt1(1);
    yt1 = Pt1(2);
    tt1 = Pt1(3);
    vt = ut(1);
    wt = ut(2);
    if abs(wt) < 1e-10
        xt = xt1 + vt * cos(tt1) * dt;
        yt = yt1 + vt * sin(tt1) * dt;
        tt = tt1 + wt * dt;
    else
        xt = xt1 + vt * power(wt, -1) * ( sin(tt1 + wt * dt) - sin(tt1));
        yt = yt1 + vt * power(wt, -1) * (-cos(tt1 + wt * dt) + cos(tt1));
        tt = tt1 + wt * dt;
    end
    Pt = [xt, yt, tt];
end

function [P, datas] = state_transition(enc, imu)
    % ファイルの読み込み %
    enc_datas = readmatrix(enc);
    imu_datas = readmatrix(imu);
    % サイズの取得 %
    size_ = length(enc_datas(:, 1));
    % 保存変数の作成 %
    x = zeros([size_ 1]);
    y = zeros([size_ 1]);
    theta = zeros([size_ 1]);
    P = [x, y, theta];
    % 速度指令値のリスト %
    vl = enc_datas(:, 2);
    vr = enc_datas(:, 3);
    v = (vl + vr) / 2;
    w = imu_datas(:, 2) * pi / 180;
    % 単位時間 %
    dt = 1;
    % 指令値行列 %
    u = [v, w];
    % 初期値の計算 %
    P(1, :) = f([0, 0, 0], u(1, :), dt);
    x(1) = P(1, 1);
    y(1) = P(1, 2);
    theta(1) = P(1, 3);
    % オドメトリ行列の計算 %
    for t = 1 : size_ - 1
        % オドメトリの計算 %
        P(t + 1, :) = f(P(t, :), u(t + 1, :), dt);
        % 値の保存 %
        x(t + 1) = P(t + 1, 1);
        y(t + 1) = P(t + 1, 2);
        theta(t + 1) = P(t + 1, 3);
    end
    P = [x, y, theta];
    datas = [vl, vr, w];
end

function dP = differential(P)
    x = P(:, 1);
    y = P(:, 2);
    theta = P(:, 3);
    size_ = length(x);
    % 偏差保存変数の作成 %
    dx = zeros([size_ 1]);
    dy = zeros([size_ 1]);
    dtheta = zeros([size_ 1]);
    % 初期値の計算 %
    dx(1) = x(1) - 0;
    dy(1) = y(1) - 0;
    dtheta(1) = theta(1) - 0;
    % 値の保存 %
    for i = 1 : size_ - 1
        dx(i) = x(i + 1) - x(i);
        dy(i) = y(i + 1) - y(i);
        dtheta(i) = theta(i + 1) - theta(i);
    end
    dP = [dx, dy, dtheta];
end

function Pr = smoothing(dP, adj)
    if adj ~= 0
        size_ = length(dP(:, 1));
        for xyt = 1 : length(dP(1, :))
            datas = dP(:, xyt);
            from = 1 + adj;
            to = size_ - adj;
            buf = zeros([adj xyt]);
            for i = from : to
                s = 0;
                % バッファ部の加算 %
                for j = 1 : adj
                    s = s + buf(j);
                end
                % 元配列部の加算 %
                for j = i : i + adj
                    s = s + datas(j);
                end
                % バッファの要素シフト %
                for j = 1 : adj - 1
                    buf(j) = buf(j + 1);
                end
                buf(adj) = datas(i);
                % 平均値の計算 %
                ave = s / (2 * adj + 1);
                % 平均値の格納 %
                datas(i) = ave;
            end
            dP(:, xyt) = datas;
        end
    end
    Pr = dP;
end

function graph(P)
    % x y のデータ取り出し %
    x = P(:, 1);
    y = P(:, 2);
    % プロット %
    plot(x, y);
    hold on
    % 最大値と最小値の取得 %
    xmin = min(x);
    ymin = min(y);
    xmax = max(x);
    ymax = max(y);
    % 中央値の算出 %
    xc = (xmin + xmax) / 2;
    yc = (ymin + ymax) / 2;
    % プロット範囲の設定 %
    xrange = xmax - xmin;
    yrange = ymax - ymin;
    padding = 1.2;
    % 正方形の作成 %
    half = padding * max(xrange, yrange) / 2;
    % プロット範囲の確定 %
    xlim([xc - half, xc + half]);
    ylim([yc - half, yc + half]);
    disp("Plot ... OK")
end

function plt(dP, Pr)
    % プロット用の配列を用意 %
    size_ = length(dP(:, 1));
    P1 = zeros([size_ 3]);
    P2 = zeros([size_ 3]);
    % 初期値の計算 %
    P1(1, 1) = dP(1, 1) + 0;
    P1(1, 2) = dP(1, 2) + 0;
    P1(1, 3) = dP(1, 3) + 0;
    P2(1, 1) = Pr(1, 1) + 0;
    P2(1, 2) = Pr(1, 2) + 0;
    P2(1, 3) = Pr(1, 3) + 0;
    % 積分 %
    for i = 1 : size_ - 1
        P1(i + 1, 1) = dP(i + 1, 1) + P1(i, 1);
        P1(i + 1, 2) = dP(i + 1, 2) + P1(i, 2);
        P1(i + 1, 3) = dP(i + 1, 3) + P1(i, 3);
        P2(i + 1, 1) = Pr(i + 1, 1) + P2(i, 1);
        P2(i + 1, 2) = Pr(i + 1, 2) + P2(i, 2);
        P2(i + 1, 3) = Pr(i + 1, 3) + P2(i, 3);
    end
    graph(P1);
    graph(P2);
    legend("Default", "Smoothed");
    xlabel("x [ mm ]");
    ylabel("y [ mm ]");
    hold off;
end

function csv(path, datas, P, dP, Pr, adj)
    size_ = length(datas(:, 1));
    Dl = datas(:, 1);
    Dr = datas(:, 2);
    Dw = datas(:, 3);
    Px = P(:, 1);
    Py = P(:, 2);
    dPx = dP(:, 1);
    dPy = dP(:, 2);
    Prx = Pr(:, 1);
    Pry = Pr(:, 2);
    codes = [Dl, Dr, Dw, Px, Py, dPx, dPy, Prx, Pry];
    codes = [Px, Py, dPx, dPy, Prx, Pry];
    writematrix(codes, path);
end

