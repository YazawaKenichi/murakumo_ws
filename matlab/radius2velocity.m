radius = [0, 50, 100, 250, 500, 750, 1000, 1250, 1500, 2000, 3000, 4000, 5000];
velo = [500, 1000, 1000, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3000, 3000, 3000];
format long
p = polyfit(radius, velo, 5);
f = poly2sym(p)
x2 = 0 : 0.1 : 10000;
y2 = polyval(p, x2);
plot(radius, velo);
hold on
plot(x2, y2);
hold off
xlim([0 5000])
ylim([500 5000])
legend("元データ", "近似曲線")
xlabel("曲率半径 [ mm ]")
ylabel("速度 [ mm / s ]")
