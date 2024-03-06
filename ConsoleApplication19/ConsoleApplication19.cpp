#include <iostream>
#include <string>
#include <vector>

class Product
{
private:

    int id;
    float weight;               // kilogram
    float price;                // dollar

public:

    Product(int _id, float _weight, float _price):
            id{ _id },
            weight{ _weight },
            price{ _price }
    {}

    std::string getInfo()
    {
        return "Info about thing under id(" + std::to_string(this->id) + "), weighs " +
                std::to_string(this->weight) + " kilogram  and costs " + std::to_string(this->price) + " dollar";
    }

    int getId()
    {
        return this->id;
    }
};

class Storage
{
private:

    int maxAmountProduct;
    std::vector<Product*> products;

public:

    Storage(int _maxAmountProduct):
            maxAmountProduct{ _maxAmountProduct }
    {}

    int getAmountProduct()
    { 
        return this->products.size();
    }

    int findId(const int id)
    {
        if (this->products.size() > 0) {

            for (size_t i{}; i < this->products.size(); i++)
            {
                if (this->products[i]->getId() == id) return i;
            }

            return -1;
        }
        else return -1;
    }

    std::string getProduct(const int id)
    {
        if(products.size() != 0 && findId(id) != -1)
        {
            return products[findId(id)]->getInfo();
        }
    }

    void addProduct(int id, float weight, float price)
    {
        if (this->products.size() == this->maxAmountProduct)
        {
            std::cout << "Storage full!" << std::endl;
        }
        else if (findId(id) != -1)
        {
            std::cout << "Product has already been added!" << std::endl;  
        }
        else
        {
            this->products.push_back(new Product{ id, weight, price });
            std::cout << "Product with id(" << id << ") successfully added!" << std::endl;
        }
    }

    void deleteProduct(int id)
    {
        if (this->products.size() > 0 && findId(id) != -1)
        {         
            std::cout << "Product with id(" << id << ") successfully delete!" << std::endl;
        }
        else
        {
            std::cout << "Storage empty!" << std::endl;
        }
    }

};

int main()
{
    Storage stor{ 2 };
    stor.addProduct(12, 200, 201);
    std::cout << stor.getProduct(12) << std::endl;
    stor.addProduct(12, 200, 200);
    std::cout << "Hello World!\n";
}