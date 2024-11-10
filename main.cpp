#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

// Clase Bucket que representa cada espacio en el hash
// Maneja la profundidad local y los valores que contiene
class Bucket
{
public:
  int localDepth;     // Profundidad local del bucket
  vector<int> values; // Valores almacenados en este bucket

  // Constructor que inicializa el bucket con la profundidad dada
  Bucket(int depth) : localDepth(depth) {}

  // Función para insertar un valor en el bucket
  bool insert(int value)
  {
    // Verifica si el valor ya está en el bucket para evitar duplicados
    for (int v : values)
    {
      if (v == value)
        return false;
    }
    values.push_back(value);
    return true;
  }

  // Función para eliminar un valor del bucket
  bool remove(int value)
  {
    // Busca el valor y lo elimina si está en el bucket
    for (auto it = values.begin(); it != values.end(); ++it)
    {
      if (*it == value)
      {
        values.erase(it);
        return true;
      }
    }
    return false;
  }

  // Función para buscar un valor en el bucket
  bool find(int value)
  {
    for (int v : values)
    {
      if (v == value)
        return true;
    }
    return false;
  }

  // Función para imprimir los valores y la profundidad del bucket
  void print()
  {
    cout << "Depth: " << localDepth << " | Values: ";
    for (int v : values)
    {
      cout << v << " ";
    }
    cout << endl;
  }
};

// Clase principal de ExtendibleHashing que implementa las operaciones solicitadas en el PDF
class ExtendibleHashing
{
public:
  int globalDepth;            // Profundidad global de la tabla
  int bucketSize;             // Tamaño máximo de cada bucket
  vector<Bucket *> directory; // Directorio de apuntadores a buckets

  // Constructor que inicializa el directorio y los buckets según la profundidad global y tamaño de bucket
  ExtendibleHashing(int depth, int size) : globalDepth(depth), bucketSize(size)
  {
    int dirSize = pow(2, globalDepth); // Tamaño inicial del directorio
    for (int i = 0; i < dirSize; ++i)
    {
      directory.push_back(new Bucket(globalDepth));
    }
  }

  // Función hash para obtener el índice del bucket usando la profundidad global
  int hash(int value)
  {
    return value & ((1 << globalDepth) - 1);
  }

  // Función de inserción (Insert) que maneja la inserción y la expansión si es necesaria
  void insert(int value)
  {
    int hashIndex = hash(value); // Índice del bucket
    Bucket *bucket = directory[hashIndex];
    if (!bucket->insert(value))
    { // Si el valor ya está, termina
      if (bucket->values.size() < bucketSize)
        return;

      // Expande la tabla si se alcanza la profundidad global
      if (bucket->localDepth == globalDepth)
      {
        expand();
      }

      // Divide el bucket actual si está lleno
      splitBucket(hashIndex);
      insert(value); // Intento de reinsertar después de dividir
    }
  }

  // Función para expandir el directorio cuando se alcanza la profundidad global
  void expand()
  {
    globalDepth++;                     // Incrementa la profundidad global
    int newSize = pow(2, globalDepth); // Nuevo tamaño del directorio
    directory.resize(newSize);         // Redimensiona el directorio
    for (int i = 0; i < newSize / 2; ++i)
    {
      directory[i + newSize / 2] = directory[i];
    }
  }

  // Función que divide el bucket cuando se alcanza el tamaño máximo
  void splitBucket(int index)
  {
    Bucket *bucket = directory[index];
    int localDepth = bucket->localDepth;
    int mask = 1 << localDepth; // Máscara para identificar el índice

    bucket->localDepth++;                               // Incrementa la profundidad local del bucket
    Bucket *newBucket = new Bucket(bucket->localDepth); // Crea un nuevo bucket

    // Reasigna los valores del bucket original
    vector<int> oldValues = bucket->values;
    bucket->values.clear();

    for (int value : oldValues)
    {
      int newIndex = hash(value);
      if (newIndex == index)
      {
        bucket->values.push_back(value);
      }
      else
      {
        newBucket->values.push_back(value);
      }
    }

    // Actualiza el directorio con el nuevo bucket
    for (int i = 0; i < directory.size(); ++i)
    {
      if (directory[i] == bucket && (i & mask) != 0)
      {
        directory[i] = newBucket;
      }
    }
  }

  // Función de búsqueda (Find) solicitada en el PDF
  bool find(int value)
  {
    int hashIndex = hash(value);              // Calcula el índice del bucket
    return directory[hashIndex]->find(value); // Llama a la función de búsqueda del bucket
  }

  // Función de eliminación (Remove) solicitada en el PDF
  void remove(int value)
  {
    int hashIndex = hash(value); // Calcula el índice del bucket
    Bucket *bucket = directory[hashIndex];
    bucket->remove(value); // Llama a la función de eliminación del bucket
  }

  // Función para imprimir los buckets y sus valores (Directorios con información en sus buckets)
  void print()
  {
    for (int i = 0; i < directory.size(); ++i)
    {
      cout << "Bucket " << i << ": ";
      directory[i]->print();
    }
  }
};

int main()
{
  // Ejemplo de uso: crea una tabla hash con profundidad global 2 y tamaño de bucket 2
  ExtendibleHashing hashTable(2, 2);

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
