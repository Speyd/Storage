#include <iostream>
#include <string>
#include <vector>

class Event
{
private:



};

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

    Product* findId(const int id)
    {
        if (this->products.size() > 0) {

            for (Product* product: products )
            {
                if (product->getId() == id) return product;
            }

            return nullptr;
        }
        else return nullptr;
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
        if(products.size() != 0 && findId(id) != UnFind)
        {
            return products[findId(id)]->getInfo();
        }
        
        return "Error!";
    }

    void addProduct(int id, float weight, float price)
    {

        Product* tempProduct{ findId(id) };

        if (this->products.size() == this->maxAmountProduct)
        {
            std::cout << "Storage full!" << std::endl;
        }
        else if (tempProduct != nullptr)
        {
            tempProduct->sumWeight(weight);
        }
        else
        {
            this->products.push_back(new Product{ id, weight, price });
            std::cout << "Product with id(" << id << ") successfully added!" << std::endl;
        }
    }

    void deleteProduct(int id)
    {
        if (this->products.size() > 0 && findId(id) != UnFind)
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