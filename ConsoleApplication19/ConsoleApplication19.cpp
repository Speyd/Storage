#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>


<<<<<<< HEAD
=======
enum enumElementProduct
{
    Null,
    Id,
    Weight,
    Price
};
class elementProduct
{
private:

    short choice;
    std::map<std::string, enumElementProduct> searchParameters;

public:

    elementProduct(const std::map<std::string, enumElementProduct>& _searchParameters):
                   choice{ 1 },
                   searchParameters{ _searchParameters }
    {}

    void inputSearchParametrs() const
    {
        int count{ 1 };

        for(auto parameter: searchParameters)
        {
            std::cout << count++ << ". " << parameter.first << std::endl;
        }

        if (this->choice < 1 || this->choice > this->searchParameters.size())
        {
            std::cout << "There is no such choice Parameters '" << this->choice << "'!" << std::endl;
        }
    }

    enumElementProduct setParametrs()
    {
    
        if (this->searchParameters.size() == 0) return Null;
        auto it = searchParameters.begin();

        do
        {
            inputSearchParametrs();
            std::cout << "Enter your choice: "; std::cin >> this->choice;

        } while (this->choice < 1 || this->choice > this->searchParameters.size());

        std::advance(it, choice - 1);
        return it->second;
    }
};


>>>>>>> 44c59be (Change all code)
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

    Product* find(std::function<bool(Product*)> hand, bool fullInfo)
    {
        if (this->products.size() > 0) {

            for (Product* product: products )
            {
                if (hand(product))
                {
                    if(fullInfo)
                    {
                        std::cout << product->getInfo() << std::endl;
                    }
                    else return product;
                       
                }
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

        Product* tempProduct{ find([id](const Product* product) {return product->getId() == id; }, 0) };

        if(tempProduct != nullptr)
        {
            return tempProduct->getInfo();
        }
        
        return "Error!";
    }

    void addProduct(int id, float weight, float price)
    {

        Product* tempProduct{ find([id](const Product* product) {return product->getId() == id; }, 0) };

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
        Product* tempProduct{ find([id](const Product* product) {return product->getId() == id; }, 0) };

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

<<<<<<< HEAD
int main()
{
    Storage stor{ 2 };
    stor.addProduct(12, 201, 201);
    stor.addProduct(13, 200, 201);
    //std::cout << stor.getProduct(12) << std::endl;
    //stor.deleteProduct(12);
   // std:cout << stor.products[0] + stor.products[1];
    std::cout << "Hello World!\n";
=======


void eventFind(elementProduct& product, Storage& stor)
{

    enumElementProduct element{ product.setParametrs() };

    float criteria;                     //TODO: разобраться с этим МЕГА костылем
    std::cout << "Enter " << (
        element == Id ? "Id" :
        element == Weight ? "weight" :
        element == Price ? "price" : "Error Product")
        << " for find: ";
    std::cin >> criteria;


    std::function<bool(Product*)> resultComparison = nullptr;
    switch (element)
    {
    case Id:
        resultComparison = [criteria, &element](Product* product) {return product->getId() == criteria; };
        break;
    case Weight:
        resultComparison = [criteria, &element](Product* product) {return product->getWeight() == criteria; };
        break;
    case Price:
        resultComparison = [criteria, &element](Product* product) {return product->getPrice() == criteria; };
        break;

    }


    std::vector<Product*> temp = stor.allFind(resultComparison);
    if (temp.size() == 0)
    {
        std::cout << "No product matching your criteria was found!" << std::endl;
        return;
    }

    for (Product* product : temp)
    {
        std::cout << product->getInfo() << std::endl;
    }
}

void eventAdd()
{

}



typedef void(*pointerEmptyFun)(elementProduct&, Storage&);
struct ItemMenu
{
    std::string textSelection{};
    pointerEmptyFun pointer;

};
class Menu
{
private:

    short choice;
    std::vector<ItemMenu> itemsMenu;
    const std::string nameMenu;

public:

    Menu(const std::string& _nameMenu, std::vector<ItemMenu>&& _itemsMenu) :
        choice{ 1 },
        nameMenu{ _nameMenu },
        itemsMenu{ _itemsMenu }
    {}


    void inputItemMenu()
    {
        size_t size{ this->itemsMenu.size() };

        std::cout << "\t\t\t" << nameMenu << std::endl;
        for (size_t i{}; i < size; i++)
        {
            std::cout << i + 1 << ". " << this->itemsMenu[i].textSelection << std::endl;
        }

        if (this->choice < 1 || this->choice > this->itemsMenu.size())
        {
            std::cout << "There is no such choice '" << this->choice << "'!" << std::endl;
        }
    }

    const short setChoicePlayer()
    {

        if (this->itemsMenu.size() == 0) return -1;

        do
        {
            inputItemMenu();
            std::cout << "Enter your choice: "; std::cin >> this->choice;
        } while (this->choice < 1 || this->choice > this->itemsMenu.size());

        return --(this->choice);
    }


    pointerEmptyFun operator[](const short _choice)
    {
        if (_choice < 0 || choice > this->itemsMenu.size() - 1)
        {
            return [](elementProduct&, Storage&) { std::cout << "Error choice" << std::endl; };
        }

        std::cout << "Your choice: " << this->itemsMenu[_choice].textSelection << std::endl;
        if (this->itemsMenu[_choice].pointer != nullptr)
        {
            return this->itemsMenu[_choice].pointer;
        }
        else
        {
            return [](elementProduct&, Storage&) { std::cout << "Nullptr pointer" << std::endl; };
        }
    }

};


int main()
{
    elementProduct element{ {{"Id", Id} , {"Weight", Weight}, {"Price", Price}} };
    Menu menu{ "Storage", {{"Add product", nullptr},{"Delete product", nullptr},{"Find product", &eventFind}} };
    Storage stor{ 2 };
    stor.addProduct(12, 201, 201);
    stor.addProduct(13, 200, 201);
    menu[menu.setChoicePlayer()](element, stor);

    return 0;
>>>>>>> 44c59be (Change all code)
}