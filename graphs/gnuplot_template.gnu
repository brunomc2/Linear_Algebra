set encoding utf8
set title "cos(α) versus R²"
set xlabel "R² (N²)"
set ylabel "cos(α)"
# set xrange [0.0:0.75]
# set yrange [-0.9:-0.0]
unset key
# set term jpeg	#set term png
set term postscript eps enhanced color
set output "grafico.eps"
plot "dados", y(x)
