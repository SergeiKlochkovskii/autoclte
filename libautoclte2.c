#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libautoclte2.h"
#include <iconv.h>

int buffer_encoding(char* input, char* output, size_t outputSize, char* to, char* from) {
    size_t inBytesLeft = strlen(input);
    size_t outBytesLeft = outputSize - 1; // Leave space for null terminator
    char* inPtr = input;
    char* outPtr = output;

    // Open conversion descriptor
    iconv_t cd = iconv_open(to, from);
    if (cd == (iconv_t)-1) {
        perror("iconv_open failed");
        return -1;
    }

    // Perform the conversion
    size_t result = iconv(cd, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft);
    if (result == (size_t)-1) {
        perror("iconv failed");
        iconv_close(cd);
        return -1;
    }

    // Null-terminate the output string
    *outPtr = '\0';

    // Close the conversion descriptor
    iconv_close(cd);

    return 0; // Success
}

int makeTuxedoCall(char *InputBuffer, char *OutputBuffer, size_t OutputBufferSize) {

    size_t isoInputBufferLen = strlen(InputBuffer) + 1;
    char* isoInputBuffer = malloc(isoInputBufferLen);
    char* utfOutputBuffer = malloc(OutputBufferSize + 1);

    memset(OutputBuffer, 0, OutputBufferSize);
    memset(isoInputBuffer, 0, isoInputBufferLen);
    memset(utfOutputBuffer, 0, OutputBufferSize + 1);

    buffer_encoding(InputBuffer, isoInputBuffer, isoInputBufferLen, "ISO-8859-1", "UTF-8");

    if (strlen(isoInputBuffer) - 1 < OutputBufferSize) {
        strcpy(utfOutputBuffer,
               "00000PRUCASER        859001WMDEMOFLOTAS    FLMANUSVC       0000000000000000000SVC_FLT 00000000000000000000000000000000000000000000000000000039020165");
        strcat(utfOutputBuffer, isoInputBuffer);
        strcat(utfOutputBuffer,
               "DEL VEHÍCULO                                NNSS                         020195VENCIMIENTO VIGILANCIA SANEAMIENTO                NSSN                         020196VENCIMIENTO VIGILANCIA PETICIÓN TÉCNICO DE AUTOS  NSSN                         020190VENCIMIENTO VIGILANCIA OTROS                      NSSN                         020178VENCIMIENTO VIGILANCIA FRAUDE                     NSSN                         020175VENCIMIENTO VIGILANCIA A.VIAJE                    NSNN                         020176VENCIMIENTO VIGILANCIA ALCOHOLEMIA                NSSN                         020174VENCIMIENTO VIGILANCIA                            NSNN                         020161VENCIMIENTO SOLICITUD CLIENTE                     NSNN                         020173VENCIMIENTO NO CUMPLIR REQUISITOS FLOTA           NSNN                         020172VENCIMIENTO CANALES                               NSSN                         020193VENCIMIENTO CAMBIO MEDIADOR                       NSNN                         020180VENCIMIENTO CAMBIO DE PRODUCTO                    NSNN                         020192VENCIMIENTO CAMBIO CANAL                          NSNN                         020146TRANSFORMACION A POLIZA DEFINITIVA RENTING        NNNN                         020185SINIESTRO TOTAL ROBO                              NNSN                         020171SINIESTRO TOTAL RC                                NNNS                         020184SINIESTRO TOTAL INCENDIO                          NNSN                         020170SIN TOMA DE EFECTO INEXACTITUD DECLARACION RIESGO SNNS                         020104SIN EFECTO                                        SNNS                         020169PERDIDA TOTAL DAÑOS                               NNSN                         020187PERDIDA TOTAL CIRA - RENOVACION                   NSSN                         020153IMPAGO PRIMA SUPLEMENTO                           SNNN                         020152IMPAGO DE RENOVACION                              SNNN                         020110IMPAGO DE PRIMERA PRIMA                           NNNN                         020135IMPAGO DE FRACCIONAMIENTO                         NNNN                         020147FINALIZACION RENTING                              NNSS                         020148FINALIZACION REASEGURO                            NNNS                         020163FALLECIMIENTO DEL TOMADOR                         NNNS                         020188DESAPARICIÓN RIESGO CIRA                          NSSN                         020164DECISION UNILATERAL DEL CLIENTE (8.14 DIAS EFECTO)NNNS                         020167COMUN ACUERDO DESPUES DE OCURRENCIA DE SINIESTRO  NNNS                         020181CAMBIO DE PRODUCTO FUERA DE VENCIMIENTO           NNSS                         020162BAJA DEL VEHICULO EN TRAFICO                      NNSS                         020186ANULACION ESPECIAL SIN EXTORNO                    NNNN                         020183ANULACION ESPECIAL ENTRE EFECTO Y VENCIMIENTO     NNNS                         020182ANULACION ESPECIAL A FIN DE EFECTO                NSNN                         020179ANULACION ESPECIAL A FECHA DE EFECTO              SNNS                         020166AGRAVACION DEL RIESGO                             NNSS                       ");



    } else {
        strcpy(OutputBuffer, "InputBuffer is too large");
        return 0;
    }

    buffer_encoding(utfOutputBuffer, OutputBuffer, OutputBufferSize,  "UTF-8", "ISO-8859-1");

    free(isoInputBuffer);
    free(utfOutputBuffer);
    return (strlen(OutputBuffer));

}