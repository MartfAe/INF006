# script_gerar_entrada_multiplas_linhas.py

import math

def gerar_nomes_em_linhas(total_nomes, nomes_por_linha_aprox, nome_base="nome_", zzz_ratio=0.1):
    """
    Gera nomes divididos em múltiplas linhas para o arquivo de entrada,
    respeitando um limite aproximado de nomes por linha.
    """
    linhas = []
    nomes_atuais_da_linha = []
    tamanho_linha_atual = 0

    # Estimativa de tamanho de um nome (ex: "nome_0000001" é 12 caracteres) + espaço = 13
    # Mude isso se o formato do nome mudar.
    tamanho_medio_nome_com_espaco = len(f"{nome_base}{0:07d}") + 1 
    
    # Define um limite de caracteres para cada linha, um pouco abaixo de MAX_TAMANHO_LINHA para segurança
    limite_char_por_linha = 2900 # Um pouco abaixo de 3001 para não correr riscos

    # Quantos nomes cabem em uma linha com base no limite de caracteres
    nomes_por_linha_estimado = math.floor(limite_char_por_linha / tamanho_medio_nome_com_espaco)
    if nomes_por_linha_estimado == 0:
        nomes_por_linha_estimado = 1 # Garante que pelo menos um nome caiba

    print(f"Estimativa de nomes por linha para caber em {limite_char_por_linha} caracteres: {nomes_por_linha_estimado}")

    # Gerar a primeira parte dos nomes (decrescente)
    for i in range(total_nomes, 0, -1):
        nome = f"{nome_base}{i:07d}"
        if tamanho_linha_atual + len(nome) + 1 > limite_char_por_linha and nomes_atuais_da_linha:
            linhas.append(" ".join(nomes_atuais_da_linha))
            nomes_atuais_da_linha = []
            tamanho_linha_atual = 0
        
        nomes_atuais_da_linha.append(nome)
        tamanho_linha_atual += len(nome) + 1 # +1 para o espaço

    # Adicionar os últimos nomes decrescentes se houver
    if nomes_atuais_da_linha:
        linhas.append(" ".join(nomes_atuais_da_linha))
        nomes_atuais_da_linha = []
        tamanho_linha_atual = 0

    # Gerar a segunda parte dos nomes (crescente, 'zzz_')
    num_zzz_nomes = math.floor(total_nomes * zzz_ratio)
    for i in range(1, num_zzz_nomes + 1):
        nome = f"zzz_{i:07d}"
        if tamanho_linha_atual + len(nome) + 1 > limite_char_por_linha and nomes_atuais_da_linha:
            linhas.append(" ".join(nomes_atuais_da_linha))
            nomes_atuais_da_linha = []
            tamanho_linha_atual = 0
        
        nomes_atuais_da_linha.append(nome)
        tamanho_linha_atual += len(nome) + 1

    # Adicionar os últimos nomes 'zzz_' se houver
    if nomes_atuais_da_linha:
        linhas.append(" ".join(nomes_atuais_da_linha))

    return "\n".join(linhas)

# Parâmetros do teste
TOTAL_DE_NOMES = 50000 # Quantidade total de nomes no arquivo
NOMES_POR_LINHA_APROX = 200 # Nomes por linha (apenas uma estimativa, o limite é por caracter)

print(f"Gerando arquivo L1Q2.in com aproximadamente {TOTAL_DE_NOMES} nomes, divididos em linhas.")

conteudo_entrada = gerar_nomes_em_linhas(TOTAL_DE_NOMES, NOMES_POR_LINHA_APROX)

with open("L1Q2.in", "w") as f:
    f.write(conteudo_entrada)

print(f"Arquivo L1Q2.in gerado com sucesso. Total de linhas: {len(conteudo_entrada.splitlines())}")
print("Verifique o arquivo L1Q2.in para confirmar que as linhas não excedem o limite de caracteres.")