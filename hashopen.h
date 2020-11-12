#include <vector>
#include <utility>
using namespace std;
template<typename TK, typename TV> 
class Hash
{
private:    
    struct Node{
        int hashCode;
        TK key;
        TV value;
    };

    int arrayLength;    
    int size;
    Node** array;

public:    
    Hash(int _length){
        arrayLength = _length;
        array = new Node*[arrayLength];
        for(int i=0;i<arrayLength;i++)
            array[i] = nullptr;
    }

    int salto(int step){
        return step;
    }

    int getHashCode(TK key_val){
      int hash  = 0;
      for(auto c : key_val) hash += int(c);
      return hash;
    }

    int bucket_count(){
        return arrayLength;
    }
    
    void insert(TK key, TV value)
    {
        int hashCode = getHashCode(key); //funcion hash   
        int index = hashCode % arrayLength;//colisiones         
        int i=0;
        while(array[index] != nullptr)
            index = (index + salto(i++)) % arrayLength ;//podemos trabajar con saltos
        array[index] = new Node(hashCode, key, value);
    }

    void insert(Node* node)
    {
        int hashCode = node->hashCode; 
        int index = hashCode % arrayLength;//colisiones   
        int i=0;              
        while(array[index] != nullptr)
            index = (index + salto(i++)) % arrayLength ;//podemos trabajar con saltos
        array[index] = node;
    }

    void rehashing(){
        int tempL = arrayLength;
        Node** temp = array;        

        arrayLength = arrayLength * 2;
        array = new Node*[arrayLength];
        for(int i=0;i<arrayLength;i++)
            array[i] = nullptr;

        for(int i=0;i<tempL;i++)
            insert(temp[i]);
            
        delete[] temp; 
    }

    TV operator[](TK key){
        //TODO
        return find(key);
    }

    TV find(TK key){
        // TODO
        int hashCode = getHashCode(key); //funcion hash   
        int index = hashCode % arrayLength;//colisiones         
        int i=0;
        while(array[index]->key != key)
            index = (index + salto(i++)) % arrayLength;
        return array[index]->value;
    }

    bool remove(TK key){
        int hashCode = getHashCode(key); //funcion hash   
        int index = hashCode % arrayLength;
      
        if(array[index]){
            delete array[index];
            array[index] = nullptr;
            
            int i=0, previ = i;
            index = (index + salto(i++)) % arrayLength;
            while(array[index]->hashCode == hashCode){
                array[previ] = array[index];
                previ = i;
                index = (index + salto(i++)) % arrayLength;
            }
            array[index] = nullptr;
            return true;
        }
        else{
            return false;
        }
    }

    std::vector<TK> getAllKeys(){
        std::vector<TK> result;
        for(int i = 0; i < arrayLength; i++){
            if(array[i]){
              result.push_back(array[i]->key);
            }
        }
        return result;        
    }
        
    std::vector<std::pair<TK, TV>> getAll(){
        std::vector<std::pair<TK, TV>> items;
        for(int i=0;i<arrayLength;i++)
          if(array[i])
            items.push_back({array[i]->key, array[i]->value});
        
        return items;
    }
};