///////<3///apruebenos///<3/////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int ultimo_pedido;

typedef struct{
	char nombre[40];
	int codigo;
	long cantidad;
 	float preciounitario;
}tProducto;


typedef struct{
	int npedido;//pedido(numero de pedido)
	long cantidad;
	float total;//costo total
}tPedido;

typedef struct{
	int codigo;//(codigo de producto)
	long cantidad;
	float precio;
	float total;
}tItem;


void mostrarMenu();
void cargarCantidadPedidos();
void listarProducto();
void agregarProducto();
void modificarProducto();
void agregarPedido();
void verPedido();
void verResumen();

int main(int argc, char *argv[]) {
	
	printf("----------------------------------------------\n");
	printf("                 BIENVENIDO\n");
	printf("----------------------------------------------\n");
	
	cargarCantidadPedidos();
	
	int opcion;
	
		do{
		
		mostrarMenu();
		
		printf("Elija una opcion\n");
		fflush(stdin);
		scanf("%d", & opcion);
		
		switch(opcion){
			
			case 1:
				listarProducto();
				break;
				
			case 2:
				agregarProducto();
				break;
				
			case 3:
				modificarProducto();
				break;
				
			case 4:
				agregarPedido();
				break;
			
			case 5:
				verPedido();
				break;
			
			case 6:
				verResumen();
				break;
			
			case 7:
				printf("Bai bai\n");
				break;
				
			default:
				printf("No existe esa opcion\n");
				break;
			}
		}while(opcion!=7);
	
	printf("----------------------------------------------\n");
	printf("   vuelvA PRonto qUE tenga BuENOS dias :)\n");
	printf("----------------------------------------------\n");
	
	return 0;
}

void cargarCantidadPedidos(){
	FILE * fdPedido=NULL;
	
	tPedido pedido;
	fdPedido=fopen("pedidos.dat", "r+b");
	
	if (fdPedido!=NULL){//numero de pedidos
		fread(&pedido,sizeof(tPedido),1,fdPedido);
		while(!feof(fdPedido)){
			ultimo_pedido++;
			fread(&pedido,sizeof(tPedido),1,fdPedido);
		}
		fclose(fdPedido);
	}
}

void mostrarMenu(){
	printf("\n************************************************\n");
	printf("\n");
	printf("\t1 - Listar Productos\n");
	printf("\t2 - Agregar Productos\n");
	printf("\t3 - Modificar Productos\n");
	printf("\t4 - Agregar Pedido\n");
	printf("\t5 - Ver Pedido\n");
	printf("\t6 - Ver Resumen\n");
	printf("\n");
	printf("\t7 - Bye bye\n");
	printf("\n************************************************\n");
}

void listarProducto(){
	
	FILE * fdstock=NULL;
	tProducto prod;
	int cantidad;
	
	printf("\n");
	
	fdstock=fopen("stocktp.dat", "rb");
	if (fdstock!=NULL){
		fread(&prod,sizeof(tProducto),1,fdstock);
		while(!feof(fdstock)){
			cantidad++;
			printf("Nombre: %s, Codigo: %i, Cantidad: %ld, Precio: $%.2f\n", prod.nombre, prod.codigo, prod.cantidad, prod.preciounitario);
			fread(&prod,sizeof(tProducto),1,fdstock);
		}
		printf("Cantidad de items: %d\n", cantidad);
		fclose(fdstock);	
	}else{
		perror("ERROR al LISTAR\n");
	}
	printf("\n");
}

void agregarProducto(){
	
	FILE * fdstock=NULL;
	tProducto prod;
	int continuar=0;
	
	fdstock=fopen("stocktp.dat", "a+b");
	if (fdstock!=NULL){
		
		do{
			printf("\n");
			
			printf("Ingrese el nombre\n");
			fflush(stdin);
			scanf("%s", & prod.nombre);
			
			printf("Ingrese el codigo\n");
			fflush(stdin);
			scanf("%d", & prod.codigo);
			
			printf("Ingrese la cantidad\n");
			fflush(stdin);
			scanf("%ld", & prod.cantidad);
			
			printf("Ingrese el precio unitario\n");
			fflush(stdin);
			scanf("%f", & prod.preciounitario);
			
			fwrite(&prod,sizeof(tProducto),1,fdstock);
		
			printf("Desea agregar otro producto? 1)Si 0)No\n");
			fflush(stdin);
			scanf("%d", &continuar);
			
		}while(continuar==1);
	
		fclose(fdstock);
	}else{
		perror("ERROR al AGREGAR\n");
	}
}

void modificarProducto(){
	
	int codigo;
	int cambiar;
	int pos=0;
	FILE * fdstock=NULL;
	tProducto prod;
	
	printf("Ingrese el codigo\n");
	scanf("%d",&codigo);
	
	fdstock=fopen("stocktp.dat", "r+b");
	if (fdstock!=NULL){
		fread(&prod,sizeof(tProducto),1,fdstock);
		
		while(!feof(fdstock) && codigo!=prod.codigo){
			pos++;
			fread(&prod,sizeof(tProducto),1,fdstock);
		}
	
		if(codigo==prod.codigo){
			printf("Se encuentra en la posicion: %d\n", pos);
			printf("Nombre: %s, Codigo: %i, Cantidad: %ld, Precio: %.2f\n", prod.nombre, prod.codigo, prod.cantidad, prod.preciounitario);
			
			
			printf("Desea cambiar el nombre?: 1)Si  0)No\n");
			fflush(stdin);
			scanf("%d", &cambiar);
			if(cambiar){//MODIFICAR
				printf("Ingrese el nombre:\n");
				scanf("%s", &prod.nombre);
			}
				
				
			printf("Desea cambiar la cantidad?: 1)Si  0)No\n");
			fflush(stdin);
			scanf("%d", &cambiar);
			if(cambiar){
				
				printf("Ingrese la cantidad:\n");
				scanf("%d", &prod.cantidad);
			}
			
			
			printf("Desea cambiar el precio por unidad?: 1)Si  0)No\n");
			fflush(stdin);
			scanf("%d", &cambiar);
			if(cambiar){
				printf("Ingrese el precio:\n");
				scanf("%f", &prod.preciounitario);
			}
		
			fseek(fdstock, pos * sizeof(tProducto), SEEK_SET);
				
			size_t size=fwrite(&prod,sizeof(tProducto),1,fdstock);
			
			if(size==sizeof(tProducto)){
				printf("Se guardo el registro con los cambios\n");
			}else{
				printf("size= %d\n", size);
			}
			
		}else{
			printf("No existe un producto con codigo: %d\n", codigo);
		}
	
		fclose(fdstock);
	
	}else{
		perror("ERROR al MODIFICAR\n ");
	}
}		

void agregarPedido(){
	
	int codigo=0;
	int cantidad=0;
	int items=0;
	float total=0;
	int continuar=0;
	
	FILE*fdstock=NULL;
	FILE*fdNPedido=NULL;
	FILE*fdPedido=NULL;
	tProducto prod;
	
	printf("Agregar pedido\n");
	
	char nombre_archivo[20];
	
	ultimo_pedido++;
	
	sprintf(nombre_archivo, "%d.dat", ultimo_pedido);
	
	printf("Nuevo archivo '%s'", nombre_archivo);
	
	fdNPedido = fopen(nombre_archivo, "a+b");
	
	if(fdNPedido!=NULL){
		do{	
			printf("Ingrese codigo del producto\n");
			scanf("%d", & codigo);
			
			fdstock = fopen("stocktp.dat", "r+b");
			if(fdstock!=NULL){
				fread(&prod,sizeof(tProducto),1,fdstock);
				while(!feof(fdstock) && codigo!=prod.codigo){
					fread(&prod,sizeof(tProducto),1,fdstock);
				}
			}
				
			if(codigo==prod.codigo){
				printf("Ingrese la cantidad\n");
				scanf("%d", &cantidad);
				if(cantidad<=prod.cantidad){
					
					items++;
					tItem item;
					item.cantidad=cantidad;
					item.codigo=codigo;
					item.precio=prod.preciounitario;
					
					total=total+cantidad*item.precio;
						
					int v=fwrite(&item,sizeof(tItem),1,fdNPedido);
					if(v==0){
						printf("Error al crear %s\n", nombre_archivo);
						perror("");
					}
				}else{
					printf("El stock disponible es %dl\n", prod.cantidad);
				}
			}else{
				printf("El codigo no pertenece a ningun producto\n");
			}

		printf("Desea continuar? 1)Si 0)No\n");
		scanf("%d", &continuar);
		
	}while(continuar==1);
				
	fclose(fdNPedido);

	if(items>0){
		
		fdPedido  = fopen("pedidos.dat", "a+b");
			
			if(fdPedido!=NULL){
				
				tPedido pedido;
				pedido.npedido=ultimo_pedido;
				pedido.cantidad=items;
				pedido.total= total;
				
				fwrite(&pedido,sizeof(tPedido),1,fdPedido);
				
				fclose(fdPedido);
				
			}
	}
		
	}else{
		printf("Se produjo un error al crear el archivo '%s'", nombre_archivo);		
		perror("");
	}
	
	
}

void verPedido(){
	
	FILE * fdPedido=NULL;
	FILE * fdNPedido=NULL;
	
	tItem item;
	tPedido pedido;
	
	int cantidad;
	int nitem;
	float preciototal;
	
	char codigo_pedido[3];	
	
	
	
	printf("\n");
	
	fdPedido=fopen("pedidos.dat", "r+b");
	
	if (fdPedido!=NULL){//numero de pedidos
		fread(&pedido,sizeof(tPedido),1,fdPedido);
		while(!feof(fdPedido)){
			cantidad++;
			printf("Pedido: %d\t$%.2f\n", pedido.npedido, pedido.total);
			fread(&pedido,sizeof(tPedido),1,fdPedido);
		}
		printf("Cantidad de pedidos: %d\n", cantidad);
		fclose(fdPedido);
		
		printf("Ingrese el pedido\n");
		scanf("%s",&codigo_pedido);
		
		fdNPedido=fopen(strcat(&codigo_pedido,".dat") , "r+b");
		
		if (fdNPedido!=NULL){
			fread(&item,sizeof(tItem),1,fdNPedido);
			while(!feof(fdNPedido)){
				preciototal = preciototal + item.precio*item.cantidad;
				printf("Producto: %d, Precio:$%.2f, Cantidad:%d\n", item.codigo,item.precio*item.cantidad,item.cantidad);
				
				fread(&item,sizeof(tItem),1,fdNPedido);
			}
			printf("Total: $%.2f\n", preciototal);
			
			fclose(fdNPedido);
		}else{
			perror("ERROR\n");
		}
			fclose(fdPedido);
	}else{
		perror("ERROR al LISTAR PEDIDOS\n");
	}
	printf("\n");
	
	//
	
}
	
void verResumen(){
	FILE * fdstock=NULL;
	FILE * fdPedido=NULL;
	FILE * fdNPedido=NULL;
	
	tProducto prod;
	tPedido pedido;
	tItem item;
	
	int cantidadprod=0;
	float dineroprod=0;
	long stock=0;
	int codigo_pedido=0;
	
	printf("\n");
	printf("----------------------------------------------\n");
	printf("              	    RESUMEN\n");
	printf("----------------------------------------------\n");
	
	fdstock=fopen("stocktp.dat", "r+b");
	
	if (fdstock!=NULL){//stock
	
		fread(&prod,sizeof(tProducto),1,fdstock);
		while(!feof(fdstock)){
			
			cantidadprod++;
			dineroprod=dineroprod+(prod.cantidad*prod.preciounitario);
			stock=stock+prod.cantidad;
			fread(&prod,sizeof(tProducto),1,fdstock);
			
		}
		
		printf("------------| PRODUCTOS |------------\n");
		printf("Cantidad de PRODUCTOS : %d\nStock : %ld\nDinero en PRODUCTOS : $%.2f\n", cantidadprod, stock, dineroprod);
		
		fclose(fdstock);
	}else{
		perror("ERROR al mostrar RESUMEN / NO hay PRODUCTOS\n");
	}
	
	
	int nitem;
	int cantidadpedidos = 0;
	float total = 0;
	int cantidaditem=0;
	printf("\n");
	
	fdPedido=fopen("pedidos.dat", "r+b");
	
	if (fdPedido!=NULL){//numero de pedidos
		fread(&pedido,sizeof(tPedido),1,fdPedido);
		while(!feof(fdPedido)){
			cantidadpedidos++;
			char str[3];
			sprintf(str, "%d.dat", pedido.npedido);
			
			fdNPedido=fopen(str , "r+b");
		
			if (fdNPedido!=NULL){
				fread(&item,sizeof(tItem),1,fdNPedido);
				while(!feof(fdNPedido)){
					total = total + item.precio*item.cantidad;
					cantidaditem += item.cantidad;
					fread(&item,sizeof(tItem),1,fdNPedido);
				}
			}
			fclose(fdNPedido);
			fread(&pedido,sizeof(tPedido),1,fdPedido);
		}
		printf("------------| PEDIDOS |------------\n");
		printf("Cantidad de pedidos: %d\nCantidad de productos pedidos: %d \n%Dinero en Pedidos: $%.2f\n", cantidadpedidos, cantidaditem,total);
		
		fclose(fdPedido);
			
	}else{
		perror("ERROR al LISTAR PEDIDOS\n");
	}
	
	printf("\n");
	
	
	
}


