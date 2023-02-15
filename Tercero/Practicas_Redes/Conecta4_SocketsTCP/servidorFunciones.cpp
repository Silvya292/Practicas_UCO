#include "./include/servidor.h"

//Lista con los usuarios guardados en el fichero
vector<Usuario> cargarUsuarios(){
    vector<Usuario> usuarios;
    Usuario aux=Usuario();
    string str;
    size_t len=0;
    
    string filename("usuariosRegistrados.txt");
    ifstream file(filename);
    if(!file){
        EXIT_FAILURE;
    }

    getline(file,str,' ');

    while(!file.eof()){
        aux.setUsername(str);
        getline(file,str,'\n');
        aux.setPassword(str);
        usuarios.push_back(aux);
        getline(file,str,' ');
    }

    file.close();
    return usuarios;
}

//Añade un nuevo usuario al fichero
bool registrarUsuario(Usuario usuario, vector<Usuario> usuarios){
    if(usuarioRepetido(usuario.getUsername(), usuarios)){
        return false;
    }

    string filename("usuariosRegistrados.txt");
    ofstream file;
    file.open(filename, ios::app);
    if(file.fail()){
        EXIT_FAILURE;
    }

    file<<"\n"<<usuario.getUsername()<<" "<<usuario.getPassword();
    file.close();

    return true;
}

//Comprueba si ya existe el nombre de usuario indicado
bool usuarioRepetido(string usuario, vector<Usuario> usuarios){
    for(int i=0;i<usuarios.size();i++){
        if(usuarios[i].getUsername()==usuario){
            return true;
        }
    }

    return false;
}

//Comprueba si la contraseña pertenece al nombre de usuario indicado
bool comprobarPassword(string password, string usuario, vector<Usuario> usuarios){
    for(int i=0;i<usuario.size();i++){
        if(usuarios[i].getUsername()==usuario){
            if(usuarios[i].getPassword()==password){
                return true;
            }
        }
    }

    return false;
}

//Comprueba si el usuario se ha registrado previamente
bool usuarioRegistrado(string usuario, vector<Usuario> usuariosIn){
    for(int i=0;i<usuariosIn.size();i++){
        if(usuario==usuariosIn[i].getUsername()){
            return true;
        }
    }

    return false;
}

//Comprueba en qué partida está el usuario
int partida(int sd, vector<Partida> partidas){
    int partidaActual=-1;
    for(int i=0;i<partidas.size();i++){
        if(partidas[i].getSdJugador1()==sd || partidas[i].getSdJugador2()==sd){
            partidaActual=i;
        }
    }
    return partidaActual;
}


