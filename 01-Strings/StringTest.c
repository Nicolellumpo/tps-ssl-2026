#include <assert.h>
#include "String.h"

int main() {
    // IsEmpty
    assert(IsEmpty(""));
    assert(!IsEmpty(" ")); 
    assert(!IsEmpty("Hola"));

    // GetLength
    assert(GetLength("") == 0);
    assert(GetLength(" ") == 1);      
    assert(GetLength("A") == 1);
    assert(GetLength("SSL") == 3);
    
    // AreEqual
    assert(AreEqual("Fede", "Fede"));
    assert(!AreEqual("Fede", "fede"));
    assert(!AreEqual("", "Hola"));    // vacío vs no vacío
    assert(!AreEqual("Hola", "Hol")); 
    
    // AreDecimalDigits
    assert(AreDecimalDigits("123"));
    assert(!AreDecimalDigits("123a"));
    assert(!AreDecimalDigits("-123")); // signo no permitido
    assert(AreDecimalDigits("0"));
    assert(AreDecimalDigits("9"));

    // Contains
    assert(Contains("Programacion", 'g'));
    assert(!Contains("Programacion", 'z'));
    assert(!Contains("", 'a'));
    assert(Contains("a", 'a'));        // string de un carácter
    assert(Contains("abc", 'a'));      // primer carácter
    assert(Contains("abc", 'c'));      // último carácter

    // ToInteger
    assert(ToInteger("123") == 123);
    assert(ToInteger("-45") == -45);
    assert(ToInteger("+7") == 7);
    assert(ToInteger("0") == 0);

    // IsLowercase
    assert(IsLowerCase("hola"));
    assert(!IsLowerCase("HOLA"));
    assert(!IsLowerCase("hOla"));      // mixto
    assert(IsLowerCase(""));  

    // Concatenate
    char buffer1[50] = "Hola ";
    Concatenate(buffer1, "Mundo");
    assert(AreEqual(buffer1, "Hola Mundo"));

    char buffer2[50] = "";
    Concatenate(buffer2, "Test");
    assert(AreEqual(buffer2, "Test"));

    char buffer3[50] = "abc";
    Concatenate(buffer3, "");
    assert(AreEqual(buffer3, "abc"));

    // Power
    char buffer4[50];
    Power(buffer4, "Hola", 3);
    assert(AreEqual(buffer4, "HolaHolaHola"));

    char buffer5[20];
    Power(buffer5, "Hola", 1);
    assert(AreEqual(buffer5, "Hola"));

    char buffer6[20];
    Power(buffer6, "x", 0);
    assert(AreEqual(buffer6, ""));

    // Reverse
    char buffer7[50] = "utn";
    Reverse(buffer7);
    assert(AreEqual(buffer7, "ntu"));
    
    char buffer8[10] = "a";
    Reverse(buffer8);
    assert(AreEqual(buffer8, "a"));    // un carácter
    
    char buffer9[10] = "oso";
    Reverse(buffer9);
    assert(AreEqual(buffer9, "oso"));  // palíndromo

    return 0;
}
