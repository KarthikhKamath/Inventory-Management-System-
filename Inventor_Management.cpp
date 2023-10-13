#include <iostream>
#include <string>
using namespace std;


//Class that stores and performs necessary operations on the product information of a particular product
//Consider each product with a unique id ie. a primary key that consists of its own information

class Product{
    private:        
    string name;
    int id;
    int quantity;
    double price;
    int totalCost;
    public:
    Product *next;

	

    Product() //Contructor for class Product sets default values for the data members
    {   
        this->name='-';
        this->id=0;
        this->quantity=0;
        this->price=0;
        this->totalCost=0;
    }
    
    //To display product information of each product
    void display()const {                                       
        cout << "Product ID: " << id << endl;
        cout << "Product Name: " << name << endl;
        cout << "Quantity in Stock: " << quantity << endl;
        cout << "Cost per Unit: $" << price << endl;
    }

    //To display details of the sale
    void sellDisplay()const{
        cout << "Customer Name:"<< name <<endl;
        cout << "Total Quantity: "<< quantity <<endl;
        cout << "Total Cost: "<< totalCost <<endl;
    }
    
	//To retrieve the product id
    int getID() const {
        return this->id;
    }

    //To retrieve the product quantity
    int getQuant() const {
        return this->quantity;
    }

    //To retrieve the product cost
    int getCost() const {
        return this->price;
    }

    //To retrieve the sale's total cost
    int gettotalCost() const {
        return this->totalCost;
    }

    // To retrieve the product name
    string getname()const{
        return this->name;
    }

	//To update the quantity of the product
    void updateQuantity(int newQuantity) {
        this->quantity = newQuantity;
    }

	//To update the cost of the product

	void updateCost(int newCost) {
        this->price = newCost;
    }

    // To set the product name
    void setname(string Name)
    {
        this->name=Name;
    }
    
    // To set the product id
    void setid(int Id){
        this->id=Id;
    }
   // To set the product price
   void setcost(int cost ){
        this->price=cost;
   }

    // To set the product quantity
   void setquantity(int qant)
   {
        this->quantity=qant;
   }

   // To set the totalcost of a sale
   void settotalcost(int tot)
   {
        this->totalCost=tot;
   }

    // declare the Class Inventory as the friend of the class
   friend class Inventory;

};

//Defines the complete inventory consisting of all the products.
//Operations on the inventory as a whole is done by iterating through its capacity and working on the products it consists of.
class Inventory{
    private:
    int capacity;
    Product *head, *tail;  //Defining pointers for linked list implementation
    int size;
    
    public:
	//Initializes the size and allocates memory for the products array

    Inventory(int );// Parametrized contructor for class Inventory sets the capacity and the other data members

    ~Inventory(); // Distructor to deallocate memory


    int display_capacity(); //Prototype for Retrieves the capacity 


	 //Prototype for Adding a new product to inventory and updating the inventory size
    void addProduct();


	//Prototype for Displaying all products in the inventory
    void displayallproducts();


	//Prototype for Searching for a particular product in the inventory and displaying its information
    void findProduct(int );


	//protoype for Function overloading - To find product by its name
	void findProduct(string );
 
	//prototype Updating quantity and cost per unit of a product
    void updateProduct(int , int , int );

    
    // friend function to prototype 
    friend void setcapacity(int ,Inventory &);


	//Prototype for Removing an existing product(if any) and updating the size and order of identification(index) of the products succeeding it
    void removeProduct(int );

    //Selling multiple products to a customer
    void sellProduct();

    friend Product operator+(const Product &, const Product &);

};
    Product operator+ (const Product &lhs, const Product &rhs){ //Operator overloader as a friend function
        Product sum;
        sum.setname(lhs.getname());      //To update sale name to customer name   
        sum.setquantity(lhs.getQuant() + rhs.getQuant());   //To update total quantity of sale
        sum.settotalcost((lhs.gettotalCost()) + (rhs.getCost()*rhs.getQuant()));    //TO update total cost of sale
        return sum;
    }

       Inventory::Inventory(int Capacity)// Parametrized contructor for class Inventory sets the capacity and the other data members
     {
        this->size=0;
        this->capacity=Capacity;
        this->head=NULL;
        this->tail=NULL;

     }
      Inventory::~Inventory() // Distructor to deallocate memory
      {
        while(head!=NULL)
        {
            Product *temp = head;
            head=head->next;
            delete temp;  
        }
      }

    int Inventory::display_capacity()
    {                                   // Retrieves the capacity 
        return (this->capacity);
}

	 //Adding a new product to inventory and updating the inventory size
     void Inventory::addProduct()
     {
        int id,quant,price;
        string name;
        if(size>=capacity) //Checking max capacity of the inventory
        {
            cout<<"The inventory is full.";
            return ;
        }

        Product* fresh=new Product(); //Make a new object of the class Product
        
        if(head==NULL)     //In case of inventory being empty and adding first product
        {                  //Both head and tail point to the first product
            head=fresh;
            tail=fresh;
        }
        else{                   //For every next product entry, head is untouched, tail points to the new product, 
            tail->next=fresh;   //ie. the latest product added
            tail=fresh;
        }
        fresh->next=NULL; //To define that the new product added is the last product(for this iteration) 
                          //and the linked list ends there
        
        cout<<"Enter the product name: ";
        cin>>name;
        fresh->setname(name); //set the product name
        
        cout<<"Enter the ID: ";
        cin>>id;
        fresh->setid(id); //set the product id

        cout<<"Enter the quantity: ";
        cin>>quant;
        fresh->setquantity(quant); // set the product quantity
        
        cout<<"Enter the cost per unit: ";
        cin>>price;
        fresh->setcost(price); // set the product price

        size++;
}

	//Displaying all products in the inventory
	inline void Inventory::displayallproducts()
    {
        if(size==0)
        {
            cout<<"\nThe Inventory is empty."<<endl;
            return ;
        }
        Product *temp = head; //To iterate through all the products in the inventory, you start from head and move next till NULL
        cout<<"\nInventory list:\n"<<endl;
        while(temp!=NULL)
        {
            temp->display();   
            cout<<"---------------------------"<<endl;
        temp=temp->next;
        }
}

	//Searching for a particular product in the inventory and displaying its information
    void Inventory::findProduct(int id)
    {
        int temp=0;
		Product *ptr=head;  //To iterate through all the products in the inventory
		while(ptr!=NULL)
        {
			
            if(ptr->getID()==id){    //Checking if product id in inventory
                ptr->display();  
				temp+=1;
            }
        ptr=ptr->next;
        }
		if(temp!=1){
        	cout<<"The product with the entered ID was not found!"<<endl;
		}
}

	//Function overloading - To find product by its name

	void Inventory::findProduct(string name)
    {
        int temp=0;
        Product *ptr=head;  //To iterate through all the products in the inventory
		while(ptr!=NULL)
        {
			
            if(ptr->getname()==name){  //Checking if product name in inventory
                ptr->display();
				temp+=1;
            }
        ptr=ptr->next;
        }
		if(temp!=1){
        	cout<<"The product with the entered Name was not found!"<<endl;
		}
}

	//Updating quantity and cost per unit of a product
    void Inventory::updateProduct(int id, int newQuantity, int newCost)
    {
		int temp=0;
        Product *ptr=head;  //To iterate through all the products in the inventory
        while(ptr!=NULL)
        {
            if(ptr->getID()==id) //Filter out product to make changes to
            {
				temp+=1;
				if(newQuantity!=0){
                ptr->updateQuantity(newQuantity);  
				}
                                                    //Update quantity and/or cost
				else if(newCost!=0){
				ptr->updateCost(newCost);
				}

                return ;

            }
        ptr=ptr->next;
        }
        
		if(temp!=1){
        	cout<<"The product with the entered ID was not found!"<<endl;
		}

}
    void Inventory::removeProduct(int id)
    {
         if(size==0)
         {
            cout<<"The Iventory is Empty."<<endl;
         }
         Product *current=head;  //defining 2 pointers that initially point to the first element(head) and its previous element(NULL) 
         Product *prev=NULL;
         
         while(current!=NULL)  //Iterating through the inventory
         {
            if(current->getID()==id) //If required product id found
            {
                if(current==head) //If that product id the first element in the inventory(linked list)
                {
                    head=current->next;  //Head must be updated 
                    delete current;
                    size--;
                    return ;
                }
                else{                      //Any element other than first
                    Product *del=current;  //defining a temporary pointer pointing to current 
                    
                    if((current->next)!=NULL)   //If product not first or last element
                    {
                    prev->next=current->next;      //Jumping over current meaning del can be deleted as prev and next are connected
                    }

                    else if((current->next==NULL)) //If the product is the LAST element in the inventory(linked list)
                    {
                    tail=prev;                     //Tail must be updated
                    tail->next=NULL;
                    }

                    cout<<"Product deleted.";
                    delete del;                  //Deleting the required product
                    
                    size--;
                    return ;
                }
            }
            else
            {
                prev=current;                   
                current=current->next;          //To continue iteration if product not found 

            }
           
         }
         
}
    void Inventory::sellProduct(){

        Product* fresh=new Product(); //Creating new product object to store new sale details
        int quant;
        string saleName;
        cout<<"Enter customer name: ";
        cin>>saleName;
        cout<<"Enter number of products: "; 
        cin>>quant;
        
        if(size==0)
        {
            cout<<"\nThe Inventory is empty."<<endl;
            return ;
        }
        
        fresh->setname(saleName); //To set name of sale to customer name
        
        for(int i=0;i<quant;i++){
            string p; 
            int q;
            cout<<"Enter product and quantity of "<<i+1<<" :"; 
            cin>>p>>q;

            int temp=0;
            Product *ptr=head;  //To iterate through all the products in the inventory
            while(ptr!=NULL)
            {
                if(ptr->getname()==p){  //Checking if product name in inventory
                    if(ptr->quantity<q){
                        cout<<"Not enough of product "<<p<<" in the inventory."<<endl;
                    }
                    int newquant = ptr->quantity - q;
                    
                    ptr->setquantity(q); //Setting to sale quantity for updating sale details before updating product details
                    
                    *fresh = *fresh + *ptr; //Using operator+ to find total quantity and cost
                    
                    ptr->updateQuantity(newquant); //Updating current product's quantity since part of/all is sold
                    
                    temp+=1;
                }
                ptr=ptr->next;
            }
            if(temp!=1){
                cout<<"The product with the entered Name was not found!"<<endl;
            }

        }
        cout<<"Details of sale: "<<endl;
        cout<<"-----------------"<<endl;
        fresh->sellDisplay(); //Displaying total quantity and cost
        
    }

// friend function definition
 void setcapacity(int val, Inventory &inventory){  // This function takes the an object of class Inventory and int value as an 
    inventory.capacity=val;                        // arguement and Updates the value of Capacity.
}


int main(){
    int value;
    int choice;
    cout<<"Enter the capacity of the inventory: ";         //Taking max capacity of the inventory from the user
    cin>>value;
    Inventory inventory(value);  //contstructor setting capacity value
   
    
	//Menu-driven execution

    while (true) {
        int ch=0;
		int se=0;
        cout<<"\nInventory Management System "<<endl;
        cout<<"1. Add a product"<<endl;
        cout<<"2. Display all the products in stock"<<endl;
        cout<<"3. Search for product by ID or Name"<<endl;
        cout<<"4. Update the existing Product's quantity or cost"<<endl;
        cout<<"5. Remove a product from the inventory"<<endl;
        cout<<"6. Update the capacity of the Inventory"<<endl;
        cout<<"7. Sell Product"<<endl;
        cout<<"8. EXIT"<<endl;

        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) {
            case 1:
                inventory.addProduct(); // Add products to the inventory
                break;
            case 2:
                {
                inventory.displayallproducts(); // display all the products in the inventory
                }
                break;
            case 3:
                {
					while(se!=3){
						cout<<"\n1. Search using Product ID"<<endl;  //Menu options for searching
						cout<<"2. Search using Product Name"<<endl;
						cout<<"3. Exit"<<endl;
						cout<<"Enter your choice: ";
        				cin>>se;

						switch(se){
							case 1:
								int id;
								cout<<"Enter the Product ID: ";
								cin>>id;
								cout<<"\n";
								inventory.findProduct(id); //Find the product through given ID
								break;

							case 2:
								string prod_name;
								cout<<"Enter the Product Name: ";
								cin>>prod_name;
								cout<<"\n";
								inventory.findProduct(prod_name); //Find the product through given name
								break;
						}
					}
                }
                break;
            case 4:
                {
					while(ch!=3){
						cout<<"\n1. Update Quantity"<<endl;         //Menu for updating product information
						cout<<"2. Update Cost per unit"<<endl;
						cout<<"3. Exit"<<endl;
						cout<<"Enter your choice: ";
        				cin>>ch;

						switch(ch){
							case 1:
								int id, quantity;
								cout<<"Enter the Product ID: ";
                    			cin>>id;
                    			cout<<"Enter the new Quantity: ";
                    			cin>>quantity;
								inventory.updateProduct(id,quantity,0); //Update product quantity
								break;
							case 2:
								int i, cost;
								cout<<"Enter the Product ID: ";
                    			cin>>i;
                    			cout<<"Enter the new Cost per unit: ";
                    			cin>>cost;
								inventory.updateProduct(i,0,cost); //Update product price
								break;
						}
					}                   
                }
                break;
            case 5:
                {
                    int id;
                    cout<<"Enter the ID of the product to be removed: ";
                    cin>>id;
                    inventory.removeProduct(id); //Remove Product form the Inventory based on the ID
                }
                break;
            case 6:
            {
                int cap;
                cout<<"The current capacity:"<<inventory.display_capacity();
                cout<<"\n Enter the capacity to be updated:";
                cin>>cap;
                setcapacity(cap,inventory);   // calling the friend function
            }
            break;
            case 7:
            {
                inventory.sellProduct();  //if user needs to sell multiple products to a customer
                cout<<"\nUpdated Product Details: "<<endl;
                cout<<"-------------------------"<<endl;
                inventory.displayallproducts();
            }
            break;
            case 8:
                exit(0);
            default:
                cout<<"Invalid choice. Please try again."<<endl;
        }
    }  
}