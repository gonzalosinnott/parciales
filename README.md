1° Parcial

Un diario requiere un sistema de publicación de avisos clasificados, el mismo deberá tener un
registro de clientes y de avisos publicados. Contará con el siguiente menú:
1) Alta de cliente: Se da de alta un cliente con nombre, apellido, y cuit. Se generará un ID único para este
cliente que se imprimirá por pantalla si el alta es correcta.
2) Modificar datos de cliente: Se ingresa el ID de cliente y se permitirá cambiar el nombre, el apellido y el cuit.
3) Baja de cliente: Se ingresa el ID del cliente y se listarán todas las publicaciones de dicho cliente. Luego se
preguntará si se quiere confirmar la eliminación, la cual implicará la eliminación de todas las publicaciones y del
cliente.
4) Publicar: Permitirá crear un nuevo aviso. Se pedirán los siguientes datos: ID de cliente, número de rubro,
texto del aviso (64 caracteres). Se generará automáticamente un identificador numérico para el aviso y se
imprimirá en pantalla.
5) Pausar publicación: Se pedirá el ID de la publicación y se imprimirá la información del cliente al que
pertenece, luego se pedirá confirmación para cambiarse de estado y se cambiará al estado "pausada".
6) Reanudar publicación: Se pedirá el ID de la publicación y se imprimirá la información del cliente al que
pertenece, luego se pedirá confirmación para cambiarse de estado y se cambiará al estado "activa".
7) Imprimir Clientes: Se imprimirá una lista de clientes con todos sus datos junto con la cantidad de avisos
activos que posee.
8) Informar: Un submenú con las siguientes opciones:
a) Cliente con más avisos.
b) Cantidad de avisos pausados.
c) Rubro con mas avisos.

Nota 0: El sistema soportará una capacidad máxima de 100 clientes y 1000 publicaciones
Nota 1: Se deberán desarrollar bibliotecas por cada entidad las cuales contendrán las funciones (Alta, Baja, Modificar, etc.).
Los informes deberán estar en una biblioteca aparte.
Nota 2: El código deberá tener comentarios con la documentación de cada una de las funciones y respetar las reglas de estilo
de la cátedra.
