# 🎨 Pixelador & Meme Generator (C + Shell)

Ferramenta de processamento de imagem de baixo nível desenvolvida em C e integrada a um script de automação Shell. O projeto permite transformar imagens em versões pixelizadas ou em **"Memes Degradados" (Deep Fried)**.

---

## 🚀 Funcionalidades

* **Processamento em C:** Algoritmo nativo para pixelização de imagens BMP 24-bit com tratamento manual de *Padding* e alinhamento de memória.
* **Automação Shell:** Script que gerencia a conversão de formatos (JPG/PNG para BMP), correção de orientação EXIF e limpeza automática de arquivos temporários.
* **Dois Modos de Saída:**
  * **Pixelização Limpa:** Reduz a resolução em blocos e exporta em JPG de alta qualidade.
  * **Modo Meme (Deep Fried):** Aplica saturação extrema, contraste elevado e compressão JPEG destrutiva (qualidade 1%) para gerar o visual degradado clássico da internet.

---

## 💻 Compatibilidade e Requisitos

O projeto pode ser executado tanto no **Android (via Termux)** quanto no **Computador (Linux, Windows ou macOS)**.

### Requisitos Gerais
* Compilador C (`gcc` ou `clang`)
* **ImageMagick** (ferramenta `convert` / `magick`)
* Ambiente Bash (Terminal Linux, Termux ou Git Bash no Windows)

---

## 🛠️ Guia de Instalação e Uso

### 📱 Opção 1: No Celular (Android via Termux)

#### 1. Atualizar repositórios e instalar dependências
```bash
pkg update && pkg upgrade -y
pkg install clang imagemagick git -y
```
#### 2. Conceder permissão de armazenamento (Opcional)
Para acessar as fotos da sua galeria diretamente pelo Termux:
```bash
termux-setup-storage
```
#### 3. Clonar e Compilar o Projeto
```bash
git clone https://github.com/sosaulo/pixelador-imagem-c.git
cd pixelador-imagem-c

clang pixelador.c -o pixelizador
chmod +x pixel.sh
```
#### 4. Executar
```bash
./pixel.sh
```
---

### 🖥️ Opção 2: No Computador (Windows via Git Bash / WSL / Linux)

#### 1. Instalar as dependências

* **Windows:**
  1. Certifique-se de ter o **Git for Windows** instalado (ele inclui o **Git Bash**).
  2. Instale o **ImageMagick** (marcando a opção para adicionar ao PATH na instalação).
  3. Instale um compilador C (como **MinGW-w64** ou **w64devkit**) para disponibilizar o comando `gcc`.
* **Linux (Ubuntu/Debian):**
  ```bash
  sudo apt update
  sudo apt install gcc imagemagick git -y
  ```
* **macOS (via Homebrew):**
  ```bash
  brew install gcc imagemagick git
  ```
#### 2. Clonar e Compilar
Com o terminal (Git Bash no Windows ou Terminal no Linux/macOS) aberto na pasta do projeto:

```bash
git clone https://github.com/sosaulo/pixelador-imagem-c.git
cd pixelador-imagem-c

gcc pixelador.c -o pixelizador
chmod +x pixel.sh
```
#### 3. Executar
```bash
./pixel.sh
```
> **Dica para VS Code no Windows:** Para rodar o script `./pixel.sh` direto no VS Code, altere o perfil do terminal integrado de *PowerShell* para **Git Bash** (clicando na seta ao lado do botão `+` no painel do terminal).
---

## ⚠️ Limites Técnicos e Performance

Como o processamento binário é feito carregando os pixels descompactados diretamente na memória RAM:

* **Tamanho Recomendado:** Imagens de até **3MB** (em formato JPG original).
* **Por que esse limite existe?** O formato BMP (utilizado na camada intermediária do C) é não-compactado. Uma foto JPG compactada de 6MB pode ocupar mais de **50MB na RAM** ao ser convertida para BMP. Em dispositivos com pouca memória (como celulares), arquivos muito grandes podem ser encerrados pelo sistema (*Out of Memory / OOM Killer*).
* **Dica:** Caso vá processar fotos em altíssima resolução (ex: 4K ou fotos de câmera de 108MP), reduza a resolução antes de enviar para o script.

---

## 🧠 Como Funciona o Algoritmo

1. **Manipulação de Bytes na RAM:** O programa lê o cabeçalho BMP e processa a matriz de cores diretamente no buffer.
2. **Cálculo de Padding:** Aplica o alinhamento de 4 bytes exigido pela especificação BMP:
   `(width * 3 + 3) & ~3`
3. **Pixelização:** Divide a matriz de pixels em blocos (N x N), calcula/extrai a cor RGB representante e a replica por todo o bloco.
4. **Processamento de Meme:** O script envia o arquivo resultante para o ImageMagick forçar filtros de deformação de cor e artefatos de compressão JPEG agressivos.

---

## 📝 Créditos

Projeto desenvolvido para fins de estudo sobre manipulação de arquivos binários, alocação de memória em C e automação em scripts Shell.
