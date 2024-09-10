def compara_resultados(arquivo1, arquivo2):
    with open(arquivo1, 'r') as f1, open(arquivo2, 'r') as f2:
        linhas_arquivo1 = f1.readlines()
        linhas_arquivo2 = f2.readlines()

        for linha1, linha2 in zip(linhas_arquivo1, linhas_arquivo2):
            partes1 = linha1.split()
            partes2 = linha2.split()

            int1_a, int2_a = int(partes1[0]), int(partes1[1])
            int1_b, int2_b = int(partes2[0]), int(partes2[1])

            if int1_a != int1_b or int2_a != int2_b:
                print(f'Diferença encontrada:\n{linha1.strip()}\n{linha2.strip()}')

# Uso
compara_resultados('output/simples.txt', 'output/correto/N10_S3_C3_M3-solution.txt')