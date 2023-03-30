% エンコーダの回転数だけでオドメトリを取る %

% FILEPATH = "desk_enc";
FILEPATH = "ideal_enc";

filepath = FILEPATH;

[x, y] = main(filepath);

glaph_plot(x, y);
legend("x", "y", "nan", "nan");
xlabel("x [ m ]");
ylabel("y [ m ]");
hold off;

function [x, y] = main(filename)
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
        tread = 0.1;    % 単位 [ m ] %
        omega = (vl - vr) / tread;    % 単位 [ rad / s = ( m / s ) / m ] %
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
    minimum = min([min(x), min(y)]);
    maximum = max([max(x), max(y)]);
    cent_grav_x = mean(x);
    cent_grav_y = mean(y);
    xrange = (cent_grav_x + max(x)) - (cent_grav_x - min(x));
    yrange = (cent_grav_x + max(y)) - (cent_grav_y - min(y));
    range = max([xrange, yrange]);
    xlim([-0.04 0.2])
    ylim([-0.04 0.2]);
end

