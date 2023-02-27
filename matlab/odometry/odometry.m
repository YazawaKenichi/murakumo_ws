% エンコーダの回転数だけでオドメトリを取る %

FILEPATH = "

filepath = FILEPATH;

[x, y] = main(filepath);

glaph_plot([x, y]);


function [x, y] = main(filename)
    % ファイルから左足の速度と右足の速度を取得 %
    datas = readmatrix(filename);
    x = zeros(length(datas(:, 1)));
    y = zeros(length(datas(:, 2)));
    theta = zeros(length(x));
    for index = 1:length(x) - 1
        vl = datas(index, 1);
        vr = datas(index, 2);
        v = (vl + vr) / 2;
        omega = (vl - vr) / tread;
        x(index + 1) = x(index) + v * cos(theta(index) + omega / 2);
        y(index + 1) = y(index) + v * sin(theta(index) + omega / 2);
    end
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

