package ar.fi.uba.cim2.model;

import java.util.List;

import ar.fi.uba.cim2.view.CheckListFuentes;
import ar.fi.uba.cim2.view.CheckListSumideros;

public class Application {
	
	private List<Fuente> fuentes;
	CheckListFuentes checkListFuentes;
	CheckListSumideros checkListSumideros;
	Configuracion configuracion;
	
	public Configuracion getConfiguracion() {
		return configuracion;
	}

	public void setConfiguracion(Configuracion configuracion) {
		this.configuracion = configuracion;
	}

	public CheckListSumideros getCheckListSumideros() {
		return checkListSumideros;
	}

	public void setCheckListSumideros(CheckListSumideros checkListSumideros) {
		this.checkListSumideros = checkListSumideros;
	}

	public CheckListFuentes getCheckListFuentes() {
		return checkListFuentes;
	}

	public void setCheckListFuentes(CheckListFuentes checkListFuentes) {
		this.checkListFuentes = checkListFuentes;
	}

	public List<Fuente> getFuentes() {
		return fuentes;
	}

	public void setFuentes(List<Fuente> fuentes) {
		this.fuentes = fuentes;
	}

	private static Application INSTANCE = null;
	 
    private Application(){}
 
    private synchronized static void createInstance() {
        if (INSTANCE == null) { 
            INSTANCE = new Application();
        }
    }
 
    public static Application getInstance() {
        createInstance();
        return INSTANCE;
    }

	

}
