#!/bin/bash

# ========================================
# CONFIGURAÇÃO (AJUSTE AQUI)
# ========================================
# Digite o nome da pasta que você criou no seu celular (sem /sdcard/)
NOME_SUA_PASTA="Pixelizador"

# Caminho completo (não mexa aqui)
PASTA_IMAGENS="/sdcard/$NOME_SUA_PASTA"
# ========================================


echo "========================================"
echo "   SUPER PROCESSADOR DE IMAGENS (BMP)"
echo "========================================"

# 1. Listar arquivos para ajudar
echo "Arquivos em $NOME_SUA_PASTA:"
ls "$PASTA_IMAGENS"
echo "----------------------------------------"

# 2. Pedir o arquivo original
read -p "Digite o nome da foto original (ex: foto.jpg): " ARQUIVO_ORIGINAL

# 3. Preparar entrada (com auto-orient para não ficar torta)
echo "[1/4] Convertendo e rotacionando para BMP..."
magick "$PASTA_IMAGENS/$ARQUIVO_ORIGINAL" -auto-orient -type truecolor entrada.bmp

if [ $? -ne 0 ]; then echo "Erro na conversão!"; exit 1; fi

# 4. Rodar o programa em C (ele pede o blockSize)
echo "[2/4] Iniciando pixelização em C..."
./pixelador

if [ $? -ne 0 ]; then echo "Erro no código C!"; exit 1; fi

# ========================================
# NOVA PARTE: ESCOLHA DO MODO
# ========================================
echo "----------------------------------------"
echo "Escolha o processamento final:"
echo "1) Apenas Pixelizar (Salvar como BMP de alta qualidade)"
echo "2) Pixelizar e DEGRADAR (Visual de Meme/Deep Fried)"
read -p "Digite 1 ou 2: " MODO_FINAL
echo "----------------------------------------"

# 5. Pedir nome de saída
read -p "Digite o nome para salvar (sem extensão): " NOME_SAIDA

# 6. Executar o Modo Escolhido
echo "[3/4] Finalizando imagem..."

if [ "$MODO_FINAL" == "1" ]; then
    # MODO 1: Converte para JPG mantendo a fidelidade da pixelização
    echo " -> Convertendo para JPG (Alta Qualidade)..."
    magick saida.bmp -quality 100 "$PASTA_IMAGENS/${NOME_SAIDA}.jpg"
    echo " -> Salvo como JPG pixelizado (limpo)."

elif [ "$MODO_FINAL" == "2" ]; then
    # MODO 2: Converte para JPG DESTRUINDO a fidelidade
    echo " -> Aplicando degradação agressiva..."
    magick saida.bmp -modulate 100,180 -contrast-stretch 2%x2% -quality 1 "$PASTA_IMAGENS/${NOME_SAIDA}.jpg"
    echo " -> Salvo como JPG degradado (visual de meme)."

else
    echo "Opção inválida. Salvando como JPG padrão."
    magick saida.bmp -quality 90 "$PASTA_IMAGENS/${NOME_SAIDA}.jpg"
fi

# 7. Limpeza Final no Termux
echo "[4/4] Limpando arquivos temporários..."
rm entrada.bmp saida.bmp

echo "========================================"
echo "   CONCLUÍDO! Verifique sua pasta.      "
echo "========================================"
