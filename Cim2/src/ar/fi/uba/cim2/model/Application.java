package ar.fi.uba.cim2.model;

import java.util.List;

import javax.swing.JFrame;

import view.Automatizacion;
import ar.fi.uba.cim2.view.CheckListFuentes;
import ar.fi.uba.cim2.view.CheckListSumideros;

public class Application {
	
	private List<Fuente> fuentes;
	CheckListFuentes checkListFuentes;
	CheckListSumideros checkListSumideros;
	Configuracion configuracion;
	Estadisticas estadisticas;
	public Estadisticas getEstadisticas() {
		return estadisticas;
	}
	public void setEstadisticas(Estadisticas estadisticas) {
		this.estadisticas = estadisticas;
	}

	Integer numeroProceso=1;
	public void incrementarProceso(){
		this.numeroProceso++;
	}
	public Integer getNumeroProceso() {
		return numeroProceso;
	}

	public void setNumeroProceso(Integer numeroProceso) {
		this.numeroProceso = numeroProceso;
	}

	Automatizacion frame;
	public Automatizacion getFrame() {
		return frame;
	}

	public void setFrame(Automatizacion frame) {
		this.frame = frame;
	}

	Tanques tanques;
	public Tanques getTanques() {
		return tanques;
	}

	public void setTanques(Tanques tanques) {
		this.tanques = tanques;
	}

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
	 
    private Application(){
    	this.tanques=new Tanques();
    	this.configuracion=new Configuracion();
    	this.estadisticas=new Estadisticas();
    }
 
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
