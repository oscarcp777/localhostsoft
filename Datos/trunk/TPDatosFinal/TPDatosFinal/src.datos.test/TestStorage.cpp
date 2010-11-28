/*
 * TestStorage.cpp
 *
 *  Created on: 04/09/2010
 *      Author: oscar
 */

#include "TestStorage.h"
#include "../src.datos.models/Block.h"
#include "../src.datos.utils/StringUtils.h"

TestStorage::TestStorage() {
	// TODO Auto-generated constructor stub

}

TestStorage::~TestStorage() {
	// TODO Auto-generated destructor stub
}
void TestStorage::testParserMails(){
	string str="Estimados= Alumnos:=";
	cout<<StringUtils::replaceAll(str,"=","+");


return;

	string mailcontent="Delivered-To: caceres.oscar7@gmail.com \n";
	mailcontent.append("Received: by 10.229.80.194 with SMTP id u2cs866451qck;\n");
	mailcontent.append(" Mon, 27 Jul 2009 09:27:02 -0700 (PDT)\n");
	mailcontent.append("MIME-Version: 1.0\n");
	mailcontent.append("Received: by 10.150.212.15 with SMTP id k15mr11403239ybg.293.1248712022214;\n");
	mailcontent.append("Mon, 27 Jul 2009 09:27:02 -0700 (PDT)\n");
	mailcontent.append("From: =?ISO-8859-1?Q?Juli=E1n_Jolivet?= <jujolivet@gmail.com>\n");
	mailcontent.append("Date: Mon, 27 Jul 2009 13:26:42 -0300\n");
	mailcontent.append("Message-ID: <eaa963290907270926r4a5fd89i603abf4cb5045539@mail.gmail.com>\n");
	mailcontent.append("Subject: Reanudacion de la materia.\n");
	mailcontent.append("To: joaenriquez@gmail.com, diego_mole@hotmail.com, karmican@yahoo.com,\n");
	mailcontent.append("	nueva_roma@hotmail.com, vpfiuba@hotmail.com, sebaz87@hotmail.com,\n");
	mailcontent.append("	dofama121@gmail.com, bart86@gmail.com, frangv38@hotmail.com,\n");
	mailcontent.append("ezequiel lab <delaled@gmail.com>, tuning1500@hotmail.com, caceres.oscar7@gmail.com,\n");
	mailcontent.append("sebastian_benevento@hotmail.com, jonathanperkes@gmail.com,\n");
	mailcontent.append("	facudelrojo@hotmail.com, magual89@hotmail.com\n");
	mailcontent.append("Content-Type: multipart/mixed; boundary=000e0cd4d91482d12a046fb26cdd\n");
	mailcontent.append("--000e0cd4d91482d12a046fb26cdd\n");
	mailcontent.append("Content-Type: multipart/alternative; boundary=000e0cd4d91482d121046fb26cdb\n");
	mailcontent.append("	--000e0cd4d91482d121046fb26cdb\n");
	mailcontent.append("Content-Type: text/plain; charset=ISO-8859-1\n");
	mailcontent.append("Content-Transfer-Encoding: quoted-printable\n");
	mailcontent.append("Estimados Alumnos:\n");
	mailcontent.append("Luego de estas semanas de cierre de la facultad debemos ponernos al d=EDa c=\n");
	mailcontent.append("on\n");
	mailcontent.append("la materia. Los items a cumplir para la practica son los siguientes.\n");
	mailcontent.append("- Parcial: es un ejercicio te=F3rico-practico obligatorio para todos y pued=\n");
	mailcontent.append("e\n");
	mailcontent.append("incluir todos los temas vistos hasta ahora. Los que tuvieron mas de 7 en lo=\n");
	mailcontent.append("s\n");
	mailcontent.append("dos parcialitos tomados hasta ahora pueden promocionar.\n");
	mailcontent.append("- Parcialitos: Los que no aprobaron los parcialitos los pueden recuperar en\n");
	mailcontent.append("forma domiciliaria. Deben traer hecho los parcialitos que no tengan\n");
	mailcontent.append("aprobados. No vamos a tomar parcialito del TP5.\n");
	mailcontent.append("- Aprobacion y firma de todos los TP's: En este caso pueden ir enviandolos\n");
	mailcontent.append("por mail y luego traerlos impresos para su firma.\n");
	mailcontent.append("Para llegar a tiempo con todo esto y poder darles la oportunidad de rendir\n");
	mailcontent.append("final (a los que los que lo deseen) durante 5 semanas que faltan para el\n");
	mailcontent.append("inicio del proximo cuatrimestre, nos vamos a juntar en la facultad en el\n");
	mailcontent.append("horario habitual, comenzando el martes 4 de agosto. Por favor* respondan to=\n");
	mailcontent.append("*dos* indicando que dia van a venir. Les sugiero que no se atracen asi\n");
	mailcontent.append("pueden liquidar la materia este cuatrimestre. Para los que no lo tienen,\n");
	mailcontent.append("	les env=EDo los enunciados de los parcialitos.\n");
	mailcontent.append("	Saludos,\n");
	mailcontent.append("Julian Jolivet\n");
	mailcontent.append("--000e0cd4d91482d121046fb26cdb\n");
	mailcontent.append("Content-Type: text/html; charset=ISO-8859-1\n");
	mailcontent.append("Content-Transfer-Encoding: quoted-printable\n");
	mailcontent.append("Estimados Alumnos:<div><br></div><div>Luego de estas semanas de cierre de l=\n");
	mailcontent.append("a facultad debemos ponernos al=A0d=EDa=A0con la materia. Los items a cumpli=\n");
	mailcontent.append("r para la practica son los siguientes.</div><div><br></div><div>- Parcial: =\n");
	mailcontent.append("es un ejercicio=A0te=F3rico-practico obligatorio para todos y puede incluir=\n");
	mailcontent.append("todos los temas vistos hasta ahora. Los que tuvieron mas de 7 en los dos p=\n");
	mailcontent.append("arcialitos tomados hasta ahora pueden promocionar.</div>\n");
	mailcontent.append("<div>- Parcialitos: Los que no aprobaron los parcialitos los pueden recuper=\n");
	mailcontent.append("ar en forma domiciliaria. Deben traer hecho los parcialitos que no tengan a=\n");
	mailcontent.append("probados. No vamos a tomar parcialito del TP5.</div><div>-=A0Aprobacion y f=\n");
	mailcontent.append("irma de todos los TP&#39;s: En este caso pueden ir enviandolos por mail y l=\n");
	mailcontent.append("uego traerlos impresos para su firma.</div>\n");
	mailcontent.append("<div><br></div><div>Para llegar a tiempo con todo esto y poder darles la op=\n");
	mailcontent.append("ortunidad de rendir final (a=A0los que los que lo deseen) durante 5 semanas=\n");
	mailcontent.append("que faltan para el inicio del proximo cuatrimestre, nos vamos a juntar en =\n");
	mailcontent.append("la facultad en el horario habitual, comenzando el martes 4 de agosto.=A0Por=\n");
	mailcontent.append("favor<b> respondan to</b><b>dos</b> indicando que dia van a venir. Les sug=\n");
	mailcontent.append("iero que no se atracen asi pueden liquidar la materia este cuatrimestre.=A0=\n");
	mailcontent.append("Para los que no lo tienen, les=A0env=EDo=A0los enunciados de los parcialito=\n");
	mailcontent.append("s.</div>\n");
	mailcontent.append("<div><br></div><div>Saludos,</div><div>Julian Jolivet</div>\n");
	mailcontent.append("--000e0cd4d91482d121046fb26cdb--\n");

	Mail* mailReal= new Mail();
	char* pcharmail=new char[mailcontent.size()];
	memcpy(pcharmail,mailcontent.c_str(),mailcontent.size()+1);
	mailReal->parseMail(pcharmail);
	cout<<mailReal->getFrom()<<endl;
	cout<<mailReal->getTo()<<endl;
	cout<<mailReal->getDate()<<endl;
	cout<<mailReal->getSubject()<<endl;
	cout<<mailReal->getMessage()<<endl;


	string textMail="From: Michael Richters <michael.richters@gmail.com> \n";
	textMail.append("To: bicyclelifestylegooglegroups.com \n");
	textMail.append("Subject: Re: {BL} Re: Shimano Roller brake\n");
	textMail.append("Date: Fri Sep 03 14:42:41 ART 2010\n");
	textMail.append("Content-Type: text/plain; charset=ISO-8859-1\n");
	textMail.append("GNU/Linux es uno de los términos empleados para referirse a la combinación del núcleo o kernel libre similar a Unix denominado Linux, que es usado con herramientas de sistema GNU. Su desarrollo es uno de los ejemplos más prominentes de software libre; todo su código fuente puede ser utilizado, modificado y redistribuido libremente por cualquiera bajo los términos de la GPL (Licencia Pública General de GNU) y otra serie de licencias libres.[1]\n");
	textMail.append("A pesar de que Linux (núcleo) es, en sentido estricto, el sistema operativo,[2] parte fundamental de la interacción entre el núcleo y el usuario (o los programas de aplicación) se maneja usualmente con las herramientas del proyecto GNU o de otros proyectos como GNOME. Sin embargo, una parte significativa de la comunidad, así como muchos medios generales y especializados, prefieren utilizar el término Linux para referirse a la unión de ambos proyectos. Para más información consulte la sección \"Denominación GNU/Linux\" o el artículo \"Controversia por la denominación GNU/Linux\".\n");
	textMail.append("A las variantes de esta unión de programas y tecnologías, a las que se les adicionan diversos programas de aplicación de propósitos específicos o generales se las denomina distribuciones. Su objetivo consiste en ofrecer ediciones que cumplan con las necesidades de un determinado grupo de usuarios. Algunas de ellas son especialmente conocidas por su uso en servidores y supercomputadoras.[3] donde tiene la cuota mas importante del mercado. Según un informe de IDC, GNU/Linux es utilizado por el 78% de los principales 500 servidores del mundo,[4] otro informe le da una cuota de mercado de % 89 en los 500 mayores supercomputadores.[5] Con menor cuota de mercado el sistema GNU/Linux también es usado en el segmento de las computadoras de escritorio, portátiles, computadoras de bolsillo, teléfonos móviles, sistemas embebidos, videoconsolas y otros dispositivos.\n");
	Mail* mail= new Mail();
	char* pchar=new char[textMail.size()];
	memcpy(pchar,textMail.c_str(),textMail.size()+1);
	mail->parseMail(pchar);
	cout<<mail->getFrom()<<endl;
	cout<<mail->getTo()<<endl;
	cout<<mail->getDate()<<endl;
	cout<<mail->getSubject()<<endl;
	cout<<mail->getMessage()<<endl;
	delete mail;
	delete pchar;

}
void TestStorage::testMails(){
	BinaryFile* file = new BinaryFile();
	Buffer* buffer = new Buffer(BLOCK_SIZE);
	Mail* mailUno = new Mail();
	Mail* mailDos = new Mail();
	mailUno->setDate("27/8/2009");
	mailUno->setFrom("richy");
	mailUno->setMessage("aprobamooooossss");
	mailUno->setSubject("trabajo practico");
	mailUno->setTo("yogui");

	file->create("files/storage/PruebaMail.dat");
	mailUno->pack(buffer);
	file->write(buffer->getData(),buffer->getBufferSize(),0);
	file->close();

	buffer->clear();
	file->open("files/storage/PruebaMail.dat");
	file->read(buffer->getData(),buffer->getMaxBytes(),0);
	file->close();
	cout << "buffer: "<<buffer->getData()<< endl;
	mailDos->unPack(buffer);

	cout << "date: "<<mailUno->getDate()<< endl;
	cout << "date: "<<mailDos->getDate()<< endl;
	delete buffer;
	delete file;
	delete mailUno;
	delete mailDos;
}
void TestStorage::testBlock(){
	BinaryFile* file = new BinaryFile();
	Block* block = new Block(200,0,0);
	Mail* mail1 = new Mail();
	//	mail1->setKey(new Key("100"));
	mail1->setDate("27/8/2009");
	mail1->setFrom("richy");
	mail1->setMessage("aprobamooooossss");
	mail1->setSubject("trabajo practico");
	mail1->setTo("yogui");

	Mail* mail2 = new Mail();
	//	mail2->setKey(new Key("101"));
	mail2->setDate("27/18/2009");
	mail2->setFrom("oscar");
	mail2->setMessage("aprobamooooossss");
	mail2->setSubject("texto de nada");
	mail2->setTo("richy");

	Mail* mail3 = new Mail();
	//	mail3->setKey(new Key("102"));
	mail3->setDate("27/38/2009");
	mail3->setFrom("richy");
	mail3->setMessage("trabajode nada de nada");
	mail3->setSubject("trabajo trabajo");
	mail3->setTo("yogui");
	Buffer* buffer= new Buffer(200);
	block->addReg(mail1);
	block->addReg(mail2);
	block->addReg(mail3);
	block->pack(buffer);
	file->create("PruebaMail.dat");
	file->write(buffer->getData(),0);
	file->close();

	Block* block2 = new Block(200,0,0);
	file->open("PruebaMail.dat");
	file->read(buffer->getData(),0);
	block->unPack(buffer);
	file->close();

	block2->print(std::cout);
	delete file;
	delete block;
	delete block2;
}
