# Implementación de Extendible Hashing en C++

Este proyecto implementa una estructura de datos de Hashing Extensible en C++, cumpliendo con las funciones solicitadas en el PDF de laboratorio. La implementación incluye las funciones de `Find`, `Insert`, `Remove` y la capacidad de imprimir los directorios con la información en sus buckets.

## Descripción del Proyecto

El **Hashing Extensible** es una técnica de hashing dinámico que permite ajustar la estructura de la tabla hash de acuerdo con el crecimiento de los datos. En esta implementación, cada bucket tiene una profundidad local que determina cuántos bits se utilizan para almacenar valores en él, mientras que el directorio tiene una profundidad global que define la cantidad de buckets disponibles en la estructura.

### Objetivos

Este proyecto cumple con los siguientes objetivos:
1. Implementar **Hashing Extensible** en C++.
2. Incluir las funciones básicas:
   - `Find`: Para buscar un valor en la estructura.
   - `Insert`: Para insertar un nuevo valor, expandiendo la tabla si es necesario.
   - `Remove`: Para eliminar un valor existente.
3. Proveer una función para imprimir el contenido de los buckets y su profundidad.

## Estructura del Código

El proyecto se compone principalmente de dos clases: `Bucket` y `ExtendibleHashing`.

### 1. Clase `Bucket`

La clase `Bucket` representa cada bucket en la estructura de hashing extensible. Contiene:
- `localDepth`: Indica la profundidad local del bucket.
- `values`: Almacena los valores que residen en el bucket.
  
**Funciones de `Bucket`:**
- `insert(int value)`: Inserta un valor si no está duplicado. Devuelve `true` si el valor fue agregado exitosamente y `false` si ya estaba en el bucket.
- `remove(int value)`: Elimina el valor si existe en el bucket.
- `find(int value)`: Busca un valor en el bucket.
- `print()`: Imprime la profundidad local y los valores en el bucket.

### 2. Clase `ExtendibleHashing`

La clase `ExtendibleHashing` es el contenedor principal que implementa el hash extensible. Usa un directorio para referenciar los buckets. Cada bucket puede expandirse y dividirse cuando se alcanzan los límites de su capacidad.

**Atributos de `ExtendibleHashing`:**
- `globalDepth`: Define la profundidad global, es decir, el número de bits usados para indexar los buckets en el directorio.
- `bucketSize`: Tamaño máximo de cada bucket.
- `directory`: Vector que almacena punteros a los buckets.

**Funciones de `ExtendibleHashing`:**
- `insert(int value)`: Calcula el índice de hash y llama a `insert` en el bucket correspondiente. Si el bucket está lleno y su profundidad local es igual a la global, la estructura se expande. De lo contrario, el bucket se divide.
- `expand()`: Duplica el tamaño del directorio para permitir más buckets y aumenta la profundidad global.
- `splitBucket(int index)`: Divide un bucket lleno en dos, distribuyendo los valores entre el bucket original y uno nuevo.
- `find(int value)`: Calcula el índice de hash y verifica si el valor está en el bucket correspondiente.
- `remove(int value)`: Elimina el valor de su bucket.
- `print()`: Imprime el contenido de cada bucket, incluyendo sus valores y profundidad.

## Ejemplo de Uso

Aquí un ejemplo de cómo utilizar esta implementación:

```cpp
int main() {
    ExtendibleHashing hashTable(2, 2); // Profundidad global inicial de 2 y tamaño máximo de bucket de 2

    hashTable.insert(10);
    hashTable.insert(22);
    hashTable.insert(5);
    hashTable.insert(3);
    hashTable.insert(8);
    hashTable.insert(15);

    cout << "Tabla Hash Extendible:" << endl;
    hashTable.print();

    cout << "\nBuscar el elemento 10: " << (hashTable.find(10) ? "Encontrado" : "No encontrado") << endl;

    hashTable.remove(10);
    cout << "\nDespués de eliminar 10:" << endl;
    hashTable.print();

    return 0;
}
```
