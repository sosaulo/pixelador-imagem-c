#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
	    unsigned short type;
    unsigned int size;
    unsigned short reserved1, reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
	    unsigned int size;
    int width, height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int img_size;
    int x_ppm, y_ppm;
    unsigned int colors;
    unsigned int important_colors;
} BMPInfoHeader;
#pragma pack(pop)

int main() {
	    int blockSize;
    printf("========================================\n");
    printf("   PIXELIZADOR DE IMAGENS (BMP 24-bit)  \n");
    printf("========================================\n\n");

    printf("[1/5] Configuração:\n");
    printf("Digite o tamanho do bloco de pixel (ex: 10, 20, 50): ");
    if (scanf("%d", &blockSize) != 1 || blockSize <= 0) {
	        printf(" -> Erro: Tamanho de bloco invalido!\n");
        return 1;
    }

    // Abertura do arquivo
    FILE *fIn = fopen("entrada.bmp", "rb");
    if (!fIn) {
	        printf("\n[ERRO] Nao foi possivel abrir 'entrada.bmp'.\n");
        printf("Certifique-se de que o arquivo esta na mesma pasta do codigo.\n");
        return 1;
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;
    fread(&header, sizeof(BMPHeader), 1, fIn);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, fIn);

    // Verificação de segurança
    if (header.type != 0x4D42) {
	        printf("\n[ERRO] O arquivo nao parece ser um BMP valido.\n");
        fclose(fIn);
        return 1;
    }

    int width = infoHeader.width;
    int height = abs(infoHeader.height);
    int rowSize = (width * 3 + 3) & ~3; // Ajuste de Padding (múltiplo de 4 bytes)

    printf("\n[2/5] Informacoes da Imagem:\n");
    printf(" -> Largura: %d px\n", width);
    printf(" -> Altura: %d px\n", height);
    printf(" -> Bits por Pixel: %d\n", infoHeader.bpp);
    printf(" -> Padding por linha (RowSize): %d bytes\n", rowSize);

    if (infoHeader.bpp != 24) {
	        printf(" -> [ERRO] Apenas imagens de 24 bits sao suportadas!\n");
        fclose(fIn);
        return 1;
    }

    // Alocação de memória
    printf("\n[3/5] Lendo pixels e alocando memoria...\n");
    unsigned char* pixelData = (unsigned char*)malloc(rowSize * height);
    if (!pixelData) {
	        printf(" -> [ERRO] Falha ao alocar memoria para a imagem!\n");
        fclose(fIn);
        return 1;
    }

    fseek(fIn, header.offset, SEEK_SET);
    fread(pixelData, 1, rowSize * height, fIn);
    fclose(fIn);

    // Processamento
    printf("[4/5] Aplicando efeito de pixelizacao (Bloco: %d)...\n", blockSize);
    for (int y = 0; y < height; y += blockSize) {
	        for (int x = 0; x < width; x += blockSize) {
	            
            int basePos = (y * rowSize) + (x * 3);
            unsigned char b = pixelData[basePos];
            unsigned char g = pixelData[basePos + 1];
            unsigned char r = pixelData[basePos + 2];

            for (int dy = 0; dy < blockSize && (y + dy) < height; dy++) {
	                for (int dx = 0; dx < blockSize && (x + dx) < width; dx++) {
	                    int currentPos = ((y + dy) * rowSize) + ((x + dx) * 3);
                    pixelData[currentPos] = b;
                    pixelData[currentPos + 1] = g;
                    pixelData[currentPos + 2] = r;
                }
            }
        }
    }

    // Salvando
    printf("[5/5] Salvando resultado em 'saida.bmp'...\n");
    FILE *fOut = fopen("saida.bmp", "wb");
    if (!fOut) {
	        printf(" -> [ERRO] Nao foi possivel criar o arquivo de saida!\n");
        free(pixelData);
        return 1;
    }

    fwrite(&header, sizeof(BMPHeader), 1, fOut);
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, fOut);
    fseek(fOut, header.offset, SEEK_SET);
    fwrite(pixelData, 1, rowSize * height, fOut);

    fclose(fOut);
    free(pixelData);

    printf("\n========================================\n");
    printf("   PROCESSO CONCLUIDO COM SUCESSO!     \n");
    printf("========================================\n");

    return 0;
}
