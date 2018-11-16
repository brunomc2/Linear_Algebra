set encoding utf8
set title "Pesos versus nota mínima considerada"
set xlabel "Nota mínima a ser considerada (média das provas)"
set ylabel "Peso"
# set xrange [0.0:0.75]
# set yrange [-0.5:1.5]
one(x) = 1
zero(x) = 0
set key
# set term jpeg	#set term png
set term postscript eps enhanced color
set output "weights.eps"
plot "../../least_squares_data/Independent_weights/test1_weight.data" with lines title "Prova 1", "../../least_squares_data/Independent_weights/test2_weight.data" with lines title "Prova 2", "../../least_squares_data/Independent_weights/report1_weight.data" with lines title "Relatório 1", "../../least_squares_data/Independent_weights/report2_weight.data" with lines title "Relatório 2"
