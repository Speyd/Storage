#include <iostream>
#include <string>
#include <vector>
#include <functional>

//typedef int (*handler)(int);

enum elementProduct
{
    Null,
    Id,
    Weight,
    Price
};


//class Menu
//{
//private:
//
//    short choice;
//    elementProduct element;
//    std::vector<std::string> eventText
//    { 
//        "Add new(to existing) product", "Delete product",
//        "Find product"
//    };
//    std::vector<std::string> criteriaText
//    {
//        "Id", "Weight", "Price"
//    };
//
//public:
//
//    Menu(const short _choice = 0, const elementProduct _element = Null):
//         choice{ _choice },
//         element{ _element }
//    {}
//
//    elementProduct getElemProd() const
//    {
//        return element;
//    }
//
//    short getChoice() const
//    {
//        return choice;
//    }
//
//    std::string getElement(const int index) const
//    {
//        return eventText[index];
//    }
//
//    void setChoice()
//    {
//        do {
//
//            for (short i{ 0 }; i < eventText.size(); i++)
//            {
//                std::cout << i + 1 << ". " << eventText[i] << std::endl;
//            }
//            std::cout << "Your choice: ";
//            std::cin >> choice;
//
//        } while (choice < 1 || choice > eventText.size());
//    }
//
//    void setElement()
//    {
//        for (short i{ 0 }; i < criteriaText.size(); i++)
//        {
//            std::cout << i + 1 << ". " << criteriaText[i] << std::endl;
//        }
//
//        int num{};
//        std::cout << "What criteria do you want to search by?: ";
//        std::cin >> num;
//
//        element = elementProduct(num);
//    }
//
//    void makeChoice()
//    {
//        setChoice();
//        if(eventText[choice].find("Find"))
//        {
//        
//        }
//    }
//
//};

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

    float getPrice() const
    {
        return price;
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

class Event
{
public:

    void eventFind(const elementProduct& element, Storage& stor)
    {

        float criteria;                     //TODO: разобраться с этим МЕГА костылем
        std::cout << "Enter " <<(
            element == Id ? "Id" :
            element == Weight ? "weight" :
            element == Price ? "price" : "Error") 
            << " for find: ";

        std::cin >> criteria;

        std::vector<Product*> temp = stor.allFind
        (
            [criteria, element](Product* product)
            {
                return element == Id && product->getId() == criteria ||
                    element == Weight && product->getWeight() == criteria ||
                    element == Price && product->getPrice() == criteria;
            }
        );

        if(temp.size() == 0)
        {
            std::cout << "No product matching your criteria was found!" << std::endl;
            return;
        }

        for(Product* product: temp)
        {
            std::cout << product->getInfo() << std::endl;
        }
    }

};

class Menu
{
private:

    short choice;
    elementProduct element;
    std::vector<std::string> eventText
    {
        "Add new(to existing) product", "Delete product",
        "Find product"
    };
    std::vector<std::string> criteriaText
    {
        "Id", "Weight", "Price"
    };

public:

    Event events;

    Menu(const short _choice = 0, const elementProduct _element = Null) :
        choice{ _choice },
        element{ _element }
    {}

    elementProduct getElemProd() const
    {
        return element;
    }

    short getChoice() const
    {
        return choice;
    }

    std::string getElement(const int index) const
    {
        return eventText[index];
    }

    void setChoice()
    {
        do {

            for (int i{ 0 }; i < eventText.size(); i++)
            {
                std::cout << i + 1 << ". " << eventText[i] << std::endl;
            }
            std::cout << "Your choice: ";
            std::cin >> choice;

        } while (choice < 1 || choice > eventText.size());

        choice--;
    }

    void setElemProd()
    {
        for (short i{ 0 }; i < criteriaText.size(); i++)
        {
            std::cout << i + 1 << ". " << criteriaText[i] << std::endl;
        }

        int num{};
        std::cout << "What criteria do you want to search by?: ";
        std::cin >> num;

        element = elementProduct(num);
    }

    void makeChoice()
    {
        setChoice();
        if (eventText[choice].find("Find") != std::string::npos)
        {
            setElemProd();
        }
    }

};

int main()
{
    Menu menu;
    Storage stor{ 2 };
    stor.addProduct(12, 201, 201);
    stor.addProduct(13, 200, 201);
    menu.makeChoice();
    if(menu.getElement(menu.getChoice()).find("Find") != std::string::npos)
    {
        menu.events.eventFind(menu.getElemProd(), stor);
    }
    //std::cout << stor.getProduct(12) << std::endl;
    //stor.deleteProduct(12);
   // std:cout << stor.products[0] + stor.products[1];
   /* for(Product* product : stor.allFind([](const Product* product) {return product->getWeight() == 2021; }))
    {
        std::cout << product->getInfo() << std::endl;
    }*/
}