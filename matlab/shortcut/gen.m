% ショートカットコースを生成 %

NORMAL = "Normal"
SHORT = "./Smoothed/Smoothed"
LENGTH = 9

compare(NORMAL, SHORT, LENGTH);

function [x, y] = get_xy(filename)
    % ファイルから座標を取得 %
    datas = readmatrix(filename);
    x = datas(:, 1);
    y = datas(:, 2);
    % w = datas(:, 3); %
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

function [x, y] = sigma(cx, cy)
    x = zeros([length(cx) 1]);
    y = zeros([length(cy) 1]);
    for i = 1 : length(cx)
        x(i) = sum(cx(1 : i));
        y(i) = sum(cy(1 : i));
    end
end

function compare(normal, short, length)
    [cx, cy] = get_xy(normal);
    [x, y] = sigma(round(cx), round(cy));
    x
    glaph_plot(x, y);

    for i = 1 : length
        [cx, cy] = get_xy(short + i);
        [x, y] = sigma(cx, cy);
        glaph_plot(x, y);
    end

    legend("normal", "short1", "short2", "short3", "short4", "short5", "short6", "short7", "short8", "short9");
    xlabel("x [ m ]");
    ylabel("y [ m ]");

    hold off;
end

