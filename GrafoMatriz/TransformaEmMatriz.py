#author --Joselito Junior--

import xlwt

verticesPartida = []
verticesChegada = []
arestaValor = []
listaVertices = []
qtdVertices = 0

def Menu():
    
    print("Digite: (Vertice1,quantidade,Vertice2)")
    print("EX: A,2,B")
    print("EX: A,10,B")
    print("Obs: A ordem de escrita indica o sentido\n")
    
def RecebeValores():
    sair = ''
    print("Para FINALIZAR o programa digite q")
    
    while(sair != 'q'):
        sair = str(input("Digite: "))
        
        if(sair != 'q'):
            partida,aresta,chegada = sair.split(",")
            verticesPartida.append(partida)
            verticesChegada.append(chegada)
            arestaValor.append(aresta)
        ExibeValoresAtuais()

def ExibeValoresAtuais():
    valores = ''
    i = 0
    print("Valores Digitados:")
    for partida in verticesPartida:
        valores += partida
        valores += "->"
        valores += arestaValor[i]
        valores += "->"
        valores += verticesChegada[i]
        valores += "\n"
        i += 1
    print(valores)
    print("Para FINALIZAR a entrada de dados digite q")

def ContaVertices():
    valorDiferente = 0
    verticeAnterior = 0
    global qtdVertices
    
    for vertice in verticesPartida:
        if not listaVertices:
            listaVertices.append(vertice)
            qtdVertices += 1
            
        for verticeListado in listaVertices:
            if vertice == verticeListado:
                valorDiferente = 0
                break
            valorDiferente += 1
            
        if valorDiferente != 0:
            listaVertices.append(vertice)
            qtdVertices += 1

    for vertice in verticesChegada:
        for verticeListado in listaVertices:
            if vertice == verticeListado:
                valorDiferente = 0
                break
            valorDiferente += 1
            
        if valorDiferente != 0:
            listaVertices.append(vertice)
            qtdVertices += 1
            
    print("Ha %d vertices" %(qtdVertices))
    listaVerticesOrdenados = sorted(listaVertices)
    print("-> Os vertices encontrados foram %s" %listaVerticesOrdenados)



def GeraMatrizExcel():
    fimEscrita = 0
    posicaoLinha = 0
    posicaoColuna = 0
    indice = 0
    listaVerticesOrdenados = []
    global qtdVertices
    
    workbook = xlwt.Workbook()
    worksheet = workbook.add_sheet(u'MatrizGerada')

    listaVerticesOrdenados = sorted(listaVertices)

    while fimEscrita < qtdVertices:
        worksheet.write(fimEscrita + 1, 0, listaVerticesOrdenados[fimEscrita])
        fimEscrita += 1
    fimEscrita = 0

    while fimEscrita < qtdVertices:
        worksheet.write(0, fimEscrita + 1, listaVerticesOrdenados[fimEscrita])
        fimEscrita += 1

    for partida in verticesPartida:
        for linhaOrdenada in listaVerticesOrdenados:
            if partida == linhaOrdenada:
                for colunaOrdenada in listaVerticesOrdenados:
                    if verticesChegada[indice] == colunaOrdenada:
                        try:
                            worksheet.write(posicaoLinha + 1, posicaoColuna + 1, arestaValor[indice])
                        except:
                            print("Valor não pode ser sobrescrito")
                        break
                    else:
                        posicaoColuna += 1
            else:
                posicaoLinha += 1
        indice += 1
        posicaoLinha = 0
        posicaoColuna = 0
        
    workbook.save("GrafoGeraMatriz.xls")
    print("--> GrafoGeraMatriz.xls gerado com sucesso")

if __name__ == "__main__":
    Menu()
    RecebeValores()
    ExibeValoresAtuais()
    ContaVertices()
    GeraMatrizExcel()
    print("Voce saiu")
