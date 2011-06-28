/**
 * 
 */
package fi.uba.drools.poker.models;

/**
 * @author oscar
 *
 */
public class Decision {
	public Action action;
	public Integer betsize;
	
	public Decision(Action action, Integer betsize) {
		super();
		this.action = action;
		this.betsize = betsize;
	}
	
	public Action getAction() {
		return action;
	}
	public void setAction(Action action) {
		this.action = action;
	}
	public Integer getBetsize() {
		return betsize;
	}
	public void setBetsize(Integer betsize) {
		this.betsize = betsize;
	}
    public String getMessageAction(){
    	return this.action.getVerb();
    }
	public String getActionDesc() {
		switch (this.action) {
		case RAISE:
			return "Usted debe subir a " + betsize + " fichas";
		
		case CHECK:
			return "Usted debe pasar";
			
		case CALL:
			return "Usted debe pagar";
			
		case BET:
			return "Usted debe apostar " + betsize + " fichas";
			
		case FOLD:
			return "Usted debe retirarse";
		
		default:
			return "No se determino ninguna accion";
		}
	}
	    
}
