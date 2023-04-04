% ideal_enc generator %

% トレッド %
tread = 0.1;
% 回したい半径 %
radius = 0.10; % [ m ] %
% 円弧の中心角 %
deg = 180;   % [ degree ] %
% 何ステップに渡って走り切るか %
n = 360;  % [ 回 ] %
% 最初のステップ数 %
n1 = 10;
% サンプリング周期 %
dt = 1;  % [ s ] %

% 円弧の長さ %
length = radius * deg * pi / 180;   % [ m ] %

% 比例定数 %
k = ((radius + tread / 2) + (radius - tread / 2)) / (radius + tread / 2);

vl = 2 * length / dt / k;
vr = 2 * length / dt - vl;

fileID = fopen("ideal_enc", "w");
for index = 0 : 0 + n1
    if index == 0 + n1
        fprintf(fileID, "%3d, %10.8f, %10.8f\n", index, 0.0, 0.0);
    else
        fprintf(fileID, "%3d, %10.8f, %10.8f\n", index, 0.01, 0.01);
    end
end
for index = n1 : n1 + n
    if index == n1 + n
        fprintf(fileID, "%3d, %10.8f, %10.8f\n", index, 0, 0);
    else
        fprintf(fileID, "%3d, %10.8f, %10.8f\n", index, vl / n, vr / n);
    end
end
for index = n1 + n : n1 + n + 10
    if index == n1 + n + 10
        fprintf(fileID, "%3d, %10.8f, %10.8f\n", index, 0.0, 0.0);
    else
        fprintf(fileID, "%3d, %10.8f, %10.8f\n", index, 0.01, 0.01);
    end
end





