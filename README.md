# Pixelador & Meme Generator (C + Termux)

Este projeto é uma ferramenta de processamento de imagem de baixo nível desenvolvida em C, integrada a um script de automação em Shell. Ele permite transformar fotos comuns em versões pixelizadas ou em "Memes Degradados" (Deep Fried).

## 🚀 Funcionalidades

* **Processamento em C**: Algoritmo para pixelização de imagens BMP 24-bit com tratamento de memória (Padding).
* **Automação Shell**: Script que gerencia conversão de formatos (JPG para BMP), correção de orientação (EXIF) e limpeza de arquivos temporários.
* **Dois Modos de Saída**:
    1. **Pixelização Limpa**: Mantém os blocos nítidos em JPG de alta qualidade.
    2. **Modo Meme (Deep Fried)**: Aplica saturação extrema e compressão destrutiva para o visual de meme degradado.

## ⚠️ Limites Técnicos e Performance

Como o processamento é feito diretamente na memória RAM (sem compressão durante a execução):
- **Tamanho de Arquivo Recomendado**: Fotos de até **3MB** (em formato JPG original).
- **Por que existe esse limite?**: O formato BMP (utilizado internamente) não possui compressão. Uma foto JPG de 6MB pode ocupar mais de 50MB na RAM quando convertida para BMP. Se o arquivo for muito grande, o processo pode ser encerrado pelo sistema (**Out of Memory**).
- **Dica**: Para fotos muito grandes, reduza a resolução antes de processar.

## 🛠️ Como Funciona o Algoritmo

O programa manipula a imagem diretamente na RAM como um buffer de bytes:
- **Padding**: Utiliza a lógica `(width * 3 + 3) & ~3` para garantir o alinhamento de 4 bytes exigido pelo formato BMP.
- **Pixelização**: Divide a imagem em grades, extrai a cor RGB de um pixel e a replica por todo o bloco.
- **Degradação**: Utiliza o ImageMagick para forçar artefatos de compressão JPEG (qualidade 1%).

## 📱 Como Usar no Termux

### Instalação

```bash
pkg install clang imagemagick
clang pixelador.c -o pixelizador
chmod +x pixel.sh
```

### Execução
```bash
./pixel.sh
```

## 📝 Créditos
Projeto desenvolvido com auxílio de Inteligêngia Artificial (Gemini, Google) para fins de estudo sobre manipulação de arquivos binários e automação.
