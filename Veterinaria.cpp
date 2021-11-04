#include <iostream>

using namespace::std;


struct Veterinaria{
    int ID;
    string Amo;
    string raza;  
    float peso;
    int edad;
};
Veterinaria solicitarLista(void){
    Veterinaria M;
    cout << "ID: ";
    cin >> M.ID;cin.ignore();
    cout << "Nombre del dueño: ";
    getline(cin, M.Amo);
    cout << "Raza: ";
    getline(cin, M.raza);
    cout << "Peso de la mascota: ";
    cin >> M.peso;cin.ignore();
    cout << "Edad de la mascota: ";
    cin >> M.edad;cin.ignore();
    return M;
}

void mostrarLista(Veterinaria M){
    cout << "Id: " << M.ID<<endl;
    cout << "Nombre del dueño: " << M.Amo<<endl;
    cout << "Raza: " << M.raza<< endl;
    cout << "Peso de la mascota: " << M.peso<<endl;
    cout << "Edad de la mascota: " << M.edad<<endl;
}

typedef Veterinaria T;
const T noValido = {-1,"","",-1,-1};

struct nodo{
    T dato;
    nodo *sig;
    nodo *ant;
};

class ListaCircularSimple{
    private:
        nodo *pInicio;
    public:
        ListaCircularSimple();
        ~ListaCircularSimple();
        void insInicio(T);
        void mostrarListaDirectoIter(T);
        void mostrarListaById(T,int);
        void deleteItem(int);
        bool empty(void);
        bool mostrarId(int);
};

ListaCircularSimple::ListaCircularSimple(void){
    pInicio = NULL;
}

ListaCircularSimple::~ListaCircularSimple(void){
    nodo *p;
    while(pInicio){
        p = pInicio;
        pInicio = pInicio->sig;
        delete p;
    }
}

void ListaCircularSimple::insInicio(T dato){
    nodo *nuevo = new nodo;
    nuevo->dato = dato;
    nuevo->sig = pInicio;
    if(pInicio != NULL)
        pInicio->ant = nuevo;
    pInicio = nuevo;
}

bool ListaCircularSimple::mostrarId(int IDref){
       if(!pInicio) 
        return false;
    else{ 
        nodo *saltarin = pInicio;
        while(saltarin && (saltarin->dato).ID != IDref) 
            saltarin = saltarin->sig; 
        if(!saltarin) 
            return false;
        else
            return true;
    } 
}

void ListaCircularSimple::mostrarListaDirectoIter(T datoB){
    int IDref;
    nodo *saltarin = pInicio;
    Veterinaria p;
    while(saltarin != NULL){
        mostrarLista(saltarin->dato);
        saltarin = saltarin->sig;
        }
    }
void ListaCircularSimple::mostrarListaById(T datoB, int idref){
    nodo *saltarin = pInicio;
    Veterinaria p;
    while(saltarin != NULL){
    	if((saltarin->dato).ID==idref){
    		mostrarLista(saltarin->dato);
    		break;
		}else{
			saltarin = saltarin->sig;
		}
        
    }
}


void ListaCircularSimple::deleteItem(int idref){
    if(!pInicio){ 
        cout << "Actualmente no hay mascotas en el sistema." << endl;
    }
    else{ 
        nodo *saltarin = pInicio;
        while(saltarin && (saltarin->dato).ID != idref) 
            saltarin = saltarin->sig; 
        if(!saltarin) 
            cout << "La mascota no está en la lista" << endl;
        else{ 
            if(!saltarin->ant && saltarin->sig){ 
                pInicio = pInicio->sig;
                pInicio->ant = NULL;
                delete saltarin;
            }
            else
                if(saltarin->ant && !saltarin->sig){
                    saltarin->ant->sig = NULL;
                    delete saltarin;
                }
                else
                    if(saltarin->ant && saltarin->sig){
                        saltarin->ant->sig = saltarin->sig;
                        saltarin->sig->ant = saltarin->ant;
                        delete saltarin;
                    }
                    else{
                        pInicio = NULL;
                        delete saltarin;
                    }
            cout << "Mascota eliminada exitosamente!" << endl;
        }
    }
}
bool ListaCircularSimple::empty(void){
    return pInicio == NULL;
}

int menu(){
    int opcion = 0;
    cout<<"VETERINARIA URIAS DE CHOTO"<<endl;
    cout << endl << "1) Agregar mascota." << endl;
    cout << "2) Mostrar Lista de mascotas." << endl;
    cout << "3) Mostrar mascota por id." << endl;
    cout << "4) Eliminar mascotas por id"<<endl;
    cout << "5) Salir." << endl;
    cout << "Opcion: ";
    cin >> opcion; cin.ignore();
    cout<<endl;
    return opcion;
}

int main(void){
    ListaCircularSimple objListaCircular;
    Veterinaria p;
    bool continuar = true;
    int idref;
do{
        switch(menu()){
            case 1: 
                p=solicitarLista();
                objListaCircular.insInicio(p);
                cout <<"Mascota almacenada exitosamente en el sistema!" << endl<<endl;
                break;
            case 2: 
                if(objListaCircular.empty())
                    cout << "No hay mascotas para mostrar " << endl;
                else{
                     objListaCircular.mostrarListaDirectoIter(p);
               }
               
                break;
             case 3: 
                if(objListaCircular.empty())
                    cout << "No hay mascotas para mostrar" << endl;
                else{
                    cout<<"ID: ";
                    cin>>idref;
                    if(objListaCircular.mostrarId(idref)==true){
                     objListaCircular.mostrarListaById(p,idref);
                    }
                else 
                cout<<"No se encontro mascota por el ID ingresado :("<<endl;
                }
                break;
            case 4: 
                  if(objListaCircular.empty())
                    cout << "No hay mascotas por eliminar" << endl;
                else{
                    cout<<"ID: ";
                    cin>>idref;
                    if(objListaCircular.mostrarId(idref))
                    objListaCircular.deleteItem(idref);
                    else
                    cout<<"Id no encontrado para eliminar mascota :("<<endl;
                }
                break;
            case 5: 
                continuar = false;
                break;
            default: 
                cout << "La opcion no es valida, favor intente de nuevo." << endl;
                break;
        }
    }while(continuar);
    return 0;
}