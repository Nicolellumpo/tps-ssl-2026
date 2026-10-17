# Análisis Comparativo de Strings en Lenguajes de Programación

---
1. ¿El tipo es parte del lenguaje en algún nivel?

    Lenguaje C: No posee ningún tipo de dato string nativo o primitivo. Aunque el lenguaje ofrece un soporte mínimo a través del compilador y el preprocesador, que reconocen el símbolo de comillas dobles (" ") para identificar una cadena literal. Sin este soporte básico a nivel de tokens, el lenguaje ni siquiera podría procesar texto de forma escrita

    Lenguaje Java: Sí, ya que en este lenguaje las cadenas son tipos de referencia basados en la string clase, no tipos de valor como int o boolean. Como resultado, una variable de cadena contiene una referencia a un objeto creado a partir de la String clase, no el valor de la cadena en sí.
    Esto permite crear cadenas como si fueran tipos primitivos, asignando un literal directamente a una variable String.

2. ¿El tipo es parte de la biblioteca?

    Lenguaje C: La bibloteca estandar no tiene tipo string pero provee a las funciones(declaradas en el header <string.h>) como strcpy (copia el contenido de una cadena origen a una cadena destino) y strlen (devuelve la longitud de la cadena) que operan sobre ese tipo.

    Lenguaje Java: La clase String, parte de java.lang, no requiere la importación de ninguna librería externa, ofreciendo una amplia gama de métodos para manipular y operar con cadenas de caracteres.

3. ¿Qué alfabeto usa?

    Lenguaje C: Utiliza el ASCII, aunque este lenguaje también posee soporte básico para Unicode. Se puede acceder al soporte básico de este último a través de biblioteca de terceros como glib, Qt o ICU
    
    Lenguaje Java: Utiliza el Unicode 

4. ¿Cómo se resuelve la alocación de memoria?

    Lenguaje C: Debido a que no existe el tipo string en C, lo que se hace en su lugar es reservar memoria con un vector de tipo char y asignar todos los caracteres en las distintas posiciones del vector.
    Ejemplo: 
    ```c
    char cadena[10] = "Hola"; 
    ```

    Lenguaje Java: La ubicación de memoria para las cadenas literales se realiza a través de un área especializada conocida como String Constant Pool. Cuando se crea un literal, el JVM primero busca si ya existe un valor idéntico en el pool; si lo encuentra, retorna esa misma referencia en lugar de crear un nuevo objeto. Sin embargo, cuando se usa el operador new (por ejemplo new String("Hola")), el JVM crea un nuevo objeto en el heap general, fuera del pool, incluso si ya existe un valor idéntico en él.
    Ejemplo:
    ```java
    String str = "Obstáculo";
    ```

5. ¿El tipo tiene mutabilidad o es inmutable?

    Lenguaje C: El tipo string es mutable.
    
    Lenguaje Java: Es inmutable.

6. ¿El tipo es un *first class citizen*?

    Lenguaje C: Los tipo string no son un "first class citizen" debido a que estos son pasados usando la primera dirección del elemento y no su tamaño. Esto genera que se los denomine "second class citizen"

    Lenguaje Java: Los string de Java son "first class citizen" que derivan de la clase String o de la clase StringBuffer. 

7. ¿Cuál es la mecánica para ese tipo cuando se los pasa como argumentos?

    Lenguaje C:
    ```c
    int main() {
        char *cadena="Este dia es bonito";
        printf("%s",cadena);
    }
    ```
    
    Lenguaje Java: 
    ```java
    public class Foo {
        public static void main(String[] args) {
            String str = "Hola";
            modificar(str);
            System.out.println(str); // imprime "Hola", sin cambios
        }

        public static void modificar(String s) {
            s = s + " Mundo";
        }
    }
    ```
    La referencia a str se pasa por valor: dentro de modificar, s apunta inicialmente al mismo objeto que str. Pero como los strings en Java son inmutables, la operación s + " Mundo" no modifica el objeto original, sino que crea uno nuevo y lo asigna a la variable local s. Por eso, al volver a main, str sigue apuntando al string original sin cambios.

8. ¿Y cuando son retornados por una función?

    Lenguaje C: Se pasan punteros. Ya que no puede devolver directamente un string como tipo nativo, lo que devuelve es un puntero a char (char*), que apunta al primer carácter de la cadena.
    
    Lenguaje Java: Se pasan referencias. Este lenguaje puede devolver directamente un String desde una función, porque es un tipo nativo (de referencia) e inmutable: la función retorna una referencia al objeto String resultante.

9.  ¿Qué nivel de soporte tiene para ASCII, Unicode, y UTF-8?

    Lenguaje C: Este lenguaje no especifica una codificación de caracteres predeterminada para sus fuentes.En ASCCI es un soprte directo, ya que los literales de caracteres suelen mapearse a códigos ASCII por defecto.
    El preprocesador del compilador GCC provee banderas para controlar 3 conjuntos de caracteres codificados: el conjunto de caracteres de entrada y los conjuntos de caracteres de ejecución estrecho y ancho. Los archivos fuente son los primeros en pasar de un conjunto de caracteres de entrada a Unicode en una etapa temprana del preprocesador.
    Los conjuntos de caracteres de ejecución afectan la manera en la que el preprocesador prepara caracteres y cadenas literales para el subsecuente uso por el compilador.

    Lenguaje Java: En el caso de Unicode, este es admitido de manera nativa, permitiendo trabajar con caracteres de prácticamente cualquier lenguaje existente. Java utiliza el esquema de codificación UTF-16 para su tipo de dato “char“.
    Los puntos de código con los valores numéricos más bajos, los cuales tienden a ocurrir más frecuentemente, son codificados usando menos bytes. Fue diseñado para ser compatible con versiones anteriores de ASCII: los primeros 128 caracteres de Unicode, que se corresponden uno a uno con ASCII, se codifican usando un solo byte con el mismo valor binario que ASCII, de manera tal que un archivo codificado en UTF-8 que utilice solo estos caracteres es idéntico a un archivo ASCII. Y dado que UTF-8 y UTF-16 son superconjuntos del estándar ASCII, Java trata a los caracteres de ASCII de 7 bits de manera idéntica.
    
    Por último, para UTF-8, Java tiene un soporte nativo, completo y estandarizado para el mismo.
