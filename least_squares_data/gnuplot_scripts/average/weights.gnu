set encoding utf8
set title "Pesos versus nota mínima considerada"
set xlabel "Nota mínima a ser considerada (média das provas)"
set ylabel "Peso"
# set xrange [0.0:0.75]
set yrange [-0.1:1.1]
set key
# set term jpeg	#set term png
set term postscript eps enhanced color
set output "weights.eps"
plot "weights.data" using 1:2 with lines title "Provas", "" using 1:3 with lines title "Relatórios"
