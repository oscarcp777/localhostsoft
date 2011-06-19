package fi.uba.drools.poker.example;

import static org.junit.Assert.assertEquals;

import org.drools.KnowledgeBase;
import org.drools.runtime.StatefulKnowledgeSession;
import org.junit.Test;

import fi.uba.drools.poker.FactoryDRL;

public class ClienteTest {
	Cliente cliente1=null;
	Cliente cliente2=null;
	Cliente cliente3=null;
	private void cargarClientes(StatefulKnowledgeSession ksession){
		// Cliente no registrado que gasta m�s de 1.000 euros
		cliente1 = new Cliente();
		cliente1.setNombre("Cliente 1");
		cliente1.setRegistrado(false);
		cliente1.setGasto(1200);   
		ksession.insert(cliente1);

		// Cliente registrado que gasta menos de 1.000 euros
		cliente2 = new Cliente();
		cliente2.setNombre("Cliente 2");
		cliente2.setRegistrado(true);
		cliente2.setGasto(800);   
		ksession.insert(cliente2);

		// Cliente registrado que gasta m�s de 1.000 euros
		cliente3 = new Cliente();
		cliente3.setNombre("Cliente 3");
		cliente3.setRegistrado(true);
		cliente3.setGasto(1600);  
		ksession.insert(cliente3);

	}
	@Test
	public void testGetNombre() {
		try {
			// Cargar las reglas
			KnowledgeBase kbase = FactoryDRL.readKnowledgeBase("Descuentos.drl");
			StatefulKnowledgeSession ksession = kbase.newStatefulKnowledgeSession();
//			KnowledgeRuntimeLogger logger = KnowledgeRuntimeLoggerFactory.newConsoleLogger(ksession);

			cargarClientes(ksession);
			ksession.fireAllRules();
			assertEquals(Float.valueOf(cliente1.getDescuento()),Float.valueOf(60));
			assertEquals(Float.valueOf(cliente2.getDescuento()),Float.valueOf(40));
			assertEquals(Float.valueOf(cliente3.getDescuento()),Float.valueOf(160));
			System.out.println("El cliente 1 tiene un descuento de " + cliente1.getDescuento() + " euros.");
			System.out.println("El cliente 2 tiene un descuento de " + cliente2.getDescuento() + " euros.");
			System.out.println("El cliente 3 tiene un descuento de " + cliente3.getDescuento() + " euros.");
//			logger.close();
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}


}
