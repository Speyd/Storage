#include <iostream>
#include <string>
#include <vector>
#include <functional>

//typedef int (*handler)(int);

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

    int getId() const
    {
        return this->id;
    }

    float getWeight() const
    {
        return this->weight;
    }

    void sumWeight(const float _weight)
    {
        this->weight += _weight;
    }


};

class Storage
{
private:

    int maxAmountProduct;
    std::vector<Product*> products;

    Product* find(std::function<bool(Product*)> hand)
    {
        if (this->products.size() > 0) {

            for (Product* product: products )
            {
                if (hand(product))
                {
                    return product;           
                }
            }

            return nullptr;
        }
        else return nullptr;
    }


public:

    std::vector<Product*> allFind(std::function<bool(Product*)> hand)
    {

        std::vector<Product*> tempProducts;

        if (this->products.size() > 0) {

            for (Product* product : products)
            {
                if (hand(product))
                {
                    tempProducts.push_back(product);
                }
            }
        }

        return tempProducts;
    }

public:

    Storage(int _maxAmountProduct):
            maxAmountProduct{ _maxAmountProduct }
    {}


    int getAmountProduct()
    { 
        return this->products.size();
    }

    std::string getProduct(const int id)
    {

        Product* tempProduct{ find([id](const Product* product) {return product->getId() == id; }) };

        if(tempProduct != nullptr)
        {
            return tempProduct->getInfo();
        }
        
        return "Error!";
    }

    void addProduct(int id, float weight, float price)
    {

        Product* tempProduct{ find([id](const Product* product) {return product->getId() == id; }) };

        if (this->products.size() == this->maxAmountProduct && tempProduct == nullptr)
        {
            std::cout << "Storage full!" << std::endl;
            return;
        }
        
        if (tempProduct != nullptr)
        {
            tempProduct->sumWeight(weight);
        }
        else
        {
            this->products.push_back(new Product{ id, weight, price });
        }
        std::cout << "Product with id(" << id << ") successfully added!" << std::endl;
    }

    void deleteProduct(int id)
    {
        Product* tempProduct{ find([id](const Product* product) {return product->getId() == id; }) };

        if (tempProduct != nullptr)
        {         
            this->products.erase(std::remove(this->products.begin(), this->products.end(), tempProduct),
                                 this->products.end());

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
    stor.addProduct(12, 201, 201);
    stor.addProduct(13, 200, 201);
    //std::cout << stor.getProduct(12) << std::endl;
    //stor.deleteProduct(12);
   // std:cout << stor.products[0] + stor.products[1];
    for(Product* product : stor.allFind([](const Product* product) {return product->getWeight() == 2021; }))
    {
        std::cout << product->getInfo() << std::endl;
    }
    std::cout << "Hello World!\n";
}