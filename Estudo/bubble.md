# Bubble Sort em Pseudocódigo 


```plaintext
INÍCIO
  PARA i DE 0 ATÉ n - 1 FAÇA
    PARA j DE 0 ATÉ n - i - 2 FAÇA
      SE vetor[j] > vetor[j + 1] ENTÃO
        temp ← vetor[j]
        vetor[j] ← vetor[j + 1]
        vetor[j + 1] ← temp
      FIMSE
    FIMPARA
  FIMPARA
FIM
```


## Observações:
- `vetor` é o array de entrada com `n` elementos.
- O algoritmo ordena os elementos do menor para o maior (ordem crescente).
- O pseudocódigo segue a lógica estruturada comum usada em aulas de lógica de programação ou Portugol.
