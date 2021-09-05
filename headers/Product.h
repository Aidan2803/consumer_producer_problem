#ifndef PRODUCT_H
#define PROCESS_H

class Product{
    private:
        int id;
        std::string type;
    public:
        Product():id(0), type("NONE"){}
        Product(int newId, std::string newType):id(newId), type(newType){}
        ~Product(){};
    
        void print_id_and_type(){
            std::cout << "id: " << id << " type: " << type << "\n";
        }
};

#endif