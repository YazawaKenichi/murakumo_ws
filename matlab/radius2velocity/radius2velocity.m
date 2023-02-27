MINI = "mini_course.txt";
LONG = "long_course.txt";
RAW = "raw_data.txt";

filepath = RAW;

ACCEL_MAX = 0.05;

[fixed, accel, decel, rect] = main(filepath);

glaph_plot([rect, fixed]);
legend("元データ", "調整後", "加速方向", "減速方向");
xlabel("距離 [ x10 mm / s ]");
ylabel("速度 [ m / s ]");
hold off;

% 半径から理想的な速度の矩形波 %
function speed_rect = radius2rect(radius_)
    radius_ = abs(radius_);
    rth1 = 0.075;
    rth2 = 0.125;
    rth3 = 0.175;
    rth4 = 0.45;
    rth5 = 0.8;
    rth6 = 1.5;
    rth7 = 2.5;

    vth1 = 1.0;
    vth2 = 1.2;
    vth3 = 1.5;
    vth4 = 2.0;
    vth5 = 2.5;
    vth6 = 2.5;
    vth7 = 2.5;
    vth8 = 2.5;
    
    res = zeros(length(radius_),1);
    
    for index = 1:length(radius_)
        if(radius_(index) < rth1)
            res(index) = vth1;
        elseif(radius_(index) < rth2)
            res(index) = vth2;
        elseif(radius_(index) < rth3)
            res(index) = vth3;
        elseif(radius_(index) < rth4)
            res(index) = vth4;
        elseif(radius_(index) < rth5)
            res(index) = vth5;
        elseif(radius_(index) < rth6)
            res(index) = vth6;
        elseif(radius_(index) < rth7)
            res(index) = vth7;
        else
            res(index) = vth8;
        end
    end
    speed_rect = res;
end

% 加速方向の鋸歯状波 %
function accel = rect2accel(rect_)
    global ACCEL_MAX;
    ref = zeros(length(rect_) ,1);
    accel_max = ACCEL_MAX;
    SAMPLING_LENGTH = 0.01;
    accel_length = accel_max * SAMPLING_LENGTH;
    % 初期値の設定 %
    ref(1) = 1;
    for index = 1:length(rect_)-1
        % 現在速度の格納 %
        v1 = ref(index);
        % 次の理想的な目標速度の格納 %
        v2 = rect_(index + 1);
        if(v2 > v1)
            if(accel_length > power(v2 - v1, 2))
                % 加速が間に合うのなら次の理想的な目標速度をそのまま次の速度として格納 %
                vref = v2;
            else
                % 加速が間に合わないのであれば現在の速度から加速しきれる速度に調整 %
                vref = sqrt(accel_length) + v1;
            end
        else
            % 減速するときは可能な限り速く減速してほしいので理想的な速度を次の速度として格納 %
            vref = v2;
        end
        ref(index + 1) = vref;
    end
    accel = ref;
end

% 減速方向の鋸歯状波 % % 要素末から処理することに注意 %
function decel = rect2decel(rect_)
    global ACCEL_MAX;
    ref = zeros(length(rect_), 1);
    imax = length(rect_);
    accel_max = ACCEL_MAX;
    SAMPLING_LENGTH = 0.01;
    accel_length = accel_max * SAMPLING_LENGTH;
    % 初期値の設定 %
    ref(imax) = max(rect_);
    for index = imax:-1:1+1
        % 現在速度の格納 %
        v3 = ref(index);
        % 次の理想的な目標速度の格納 %
        v2 = rect_(index - 1);
        if(v2 > v3)
            if(accel_length >= power(v3 - v2, 2))
                % 減速が間に合うのならその値を次の速度として格納 %
                vref = v2;
            else
                % 減速が間に合わないのであれば現在の速度から減速しきれる速度に調整 %
                vref = sqrt(accel_length) + v3;
            end
        else
            % 加速の時は加速する前の理想的な速度を次の速度として代入 %
            vref = v2;
        end
        ref(index - 1) = vref;
    end
    decel = ref;
end

% 二つの配列から各要素で小さい値を取る %
function minimum =  minimum(a, b)
    res = zeros(length(a),1);
    for index = 1:length(a)
        res(index) = min(a(index), b(index));
    end
    minimum = res;
end

function [fixed, accel, decel, rect] = main(filename)
    % ファイルからインデックスと半径を取得 %
    datas = readmatrix(filename);
    % ２列目の内容を取得 %
    radius_raw = datas(:, 2);
    % 矩形波の作成 %
    rect = radius2rect(radius_raw);
    % 加速の波形 %
    accel = rect2accel(rect);
    % 減速の波形 %
    decel = rect2decel(rect);
    % 加速の波形と減速の波形から低い方を取る %
    mount = minimum(accel, decel);
    fixed = mount;
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





