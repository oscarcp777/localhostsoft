package fi.uba.drools.poker;

import org.drools.KnowledgeBase;
import org.drools.KnowledgeBaseFactory;
import org.drools.builder.KnowledgeBuilder;
import org.drools.builder.KnowledgeBuilderError;
import org.drools.builder.KnowledgeBuilderErrors;
import org.drools.builder.KnowledgeBuilderFactory;
import org.drools.builder.ResourceType;
import org.drools.io.ResourceFactory;

public class FactoryDRL {
	public static KnowledgeBase readKnowledgeBase(String drl) {
	 KnowledgeBuilder kbuilder = 
	 KnowledgeBuilderFactory.newKnowledgeBuilder();
	 kbuilder.add(ResourceFactory.newClassPathResource(drl),ResourceType.DRL);
	 KnowledgeBuilderErrors errors = kbuilder.getErrors();
	 if (errors.size() > 0) {
	  for (KnowledgeBuilderError error: errors) {
	   System.err.println(error);
	  }
	  throw new IllegalArgumentException("Could not parse knowledge. :"+drl);
	 }
	 
	 KnowledgeBase kbase = KnowledgeBaseFactory.newKnowledgeBase();
	 kbase.addKnowledgePackages(kbuilder.getKnowledgePackages());
	 return kbase;
	}
	

}
