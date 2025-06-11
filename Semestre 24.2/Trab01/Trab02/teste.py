import random

def generate_test_file(filename, num_names=10):
    """Gera um arquivo de teste com nomes reais selecionados aleatoriamente."""
    # Lista de nomes reais
    names = [
        "Maria", "João", "Ana", "Bruno", "Carla", "Luiza", "Pedro", "Juliana", 
        "Roberto", "Fernanda", "Gustavo", "Camila", "Lucas", "Mariana", 
        "Daniel", "Beatriz", "Ricardo", "Patrícia", "Sofia", "Eduardo", 
        "Letícia", "Gabriel", "Larissa", "Vitor", "Manuela", "Thiago", 
        "Isabela", "Leonardo", "Renata", "Felipe", "Simone", "Rodrigo", 
        "Yara", "Diego", "Clara", "Vinícius", "Daniela", "Matheus", "Luana", 
        "Brenda", "André", "Alice", "Giovana", "Rafael", "Débora", 
        "Henrique", "Estela", "Samuel", "Roberta", "Marcelo", "Júlia", 
        "Carlos", "Bianca", "Cecília", "Otávio", "Helena", "Alexandre", 
        "Lorena", "Emanuel", "Valentina", "Victor", "Eduarda", "Flávia", 
        "Ruan", "Melissa", "Sophia", "Enzo", "Sarah", "Mirela", "Davi", 
        "Joaquim", "Isis", "Bárbara", "Antônio", "Marlene", "Icaro", 
        "Júlio", "Aline", "Jussara", "Scooby", "Jujuba"
    ]

    # Cria o arquivo e escreve nomes aleatórios
    with open(filename, 'w') as file:
        for _ in range(num_names):
            file.write(random.choice(names) + "\n")
    
    print(f"Arquivo de teste '{filename}' gerado com {num_names} nomes aleatórios.")

if __name__ == "__main__":
    generate_test_file("L1Q2.in", num_names=20)
