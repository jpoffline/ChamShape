set term png
set output "p.png"

plot "data/run_1007Fx.dat" u 1:2 w l, "data/run_1007Fy.dat" u 1:2 w l
