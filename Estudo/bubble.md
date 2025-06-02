# Bubble Sort em Pseudocódigo 

''' 
procedimento BubbleSort(lista A de n elementos)
  para i de 0 até n-2
    para j de 0 até n-i-2
      se A[j] > A[j+1] então
        trocar(A[j], A[j+1])
      fim_se
    fim_para
  fim_para
fim_procedimento 
'''