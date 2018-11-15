set encoding utf8
set title "Pesos versus nota mínima considerada"
set xlabel "Nota mínima a ser considerada (média das provas)"
set ylabel "Peso"
# set xrange [0.0:0.75]
set yrange [-0.1:1.1]
set key
# set term jpeg	#set term png
set term postscript eps enhanced color
set output "grafico.eps"
plot "../../../least_squares_data/Average/Domain_barrier/average_test_weight.data" with lines title "Provas", "../../../least_squares_data/Average/Domain_barrier/average_report_weight.data" with lines title "Relatórios"
