% ショートカットコースを生成 %

NORMAL = "Normal"

splitter(NORMAL)

% FILE 内容を x, y に分けて別のファイルに保存 %
function splitter(file)
    [x, y, q] = get_xyw(file);
    path = append(file, "X")
    save_plot(x, path);
    path = append(file, "Y")
    save_plot(y, path);
end

function [x, y, w] = get_xyw(filename)
    % ファイルから座標を取得 %
    datas = readmatrix(filename);
    x = datas(:, 1);
    y = datas(:, 2);
    w = datas(:, 3);
end

function save_plot(A, path)
    writematrix(A, path)
end

