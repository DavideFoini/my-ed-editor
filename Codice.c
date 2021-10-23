#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//strutture
typedef struct comando{
    struct comando * p;
    struct comando * n;
    long int i1;
    long int i2;
}comando_t;

typedef comando_t * storico;

typedef struct text{
    char * value;
    struct text * p;
    struct text * n;
}text_t;

typedef struct riga{
    long int index;
    struct riga * p;
    struct riga * n;
    text_t * first;
    text_t * last;
    text_t * testo;
}riga_t;

typedef riga_t * documento;

char * file;
documento testa;
documento coda;
storico cronotesta;
storico cronocoda;
long int ud=0;
long int rd=0;
int sentinella=0;


//FUNZIONI DOCUMENTO
documento inizializza_documento(long int i){
    documento doc2;
    riga_t * r=malloc(sizeof(riga_t));
    text_t * t=malloc(sizeof(text_t));
    r->index=i;
    r->n=NULL;
    r->p=NULL;
    t->value=NULL;
    t->n=NULL;
    t->p=NULL;
    r->testo=t;
    r->first=t;
    r->last=t;
    doc2=r;
    coda=doc2;
    return doc2;
}

//FUNZIONI STORICO
storico aggiungi_storico(storico cronologia, long int i1, long int i2){
    comando_t * cm=malloc(sizeof(comando_t));
    storico cm1,cm2;
    cm->i1=i1;
    cm->i2=i2;
    cm->n=NULL;

    if(cronologia->n!=NULL) { //se ho un d o c non posso più fare redo
        cm1=cronologia->n;
        while(cm1!=NULL)
        {
            cm2=cm1;
            //printf("libero %li,%li%c \n",cm2->i1,cm2->i2,cm2->input);
            cm1=cm1->n;
            free(cm2);
        }
    }
    cm->p=cronologia;
    cronologia->n=cm;
    ud=ud+1;
    return cm;
}
//PRINT
void esegui_print(documento doc,long int ind1,long int ind2){
    documento d=NULL;
    d=doc;
    int righe_stampate=0;

    if(labs(ind1-testa->index)<=labs(ind1-coda->index))
        d=testa;
    else
        d=coda;

    if(ind1==0){
        fputs(".\n", stdout);
        if(ind2==0)
            return;
        righe_stampate=righe_stampate+1;
    }
    if(d!=NULL) {
        if (d->index<ind1) {
            while (d->index<ind1 && d->n!=NULL)
                d = d->n;
        }
        if (d->index>ind1) {
            while (d->index>ind1 && d->p!=NULL)
                d = d->p;
        }
    }
    while(d!=NULL&&d->index>=ind1&&d->index<=ind2){
        if(d->testo==NULL)
            fputs(".\n", stdout);
        else {
            if(d->testo->value!=NULL) {
                fputs(d->testo->value, stdout);
                fputs("\n", stdout);
            }
            else
                fputs(".\n", stdout);
        }
        d=d->n;
        righe_stampate=righe_stampate+1;
    }

    while(righe_stampate<=(ind2-ind1)){
        fputs(".\n", stdout);
        righe_stampate=righe_stampate+1;
    }
}

//CHANGE
void inserisci_riga(documento doc, char * v, long int i) //INSERISCE O MODIFICA LA RIGA ALL'INDICE I
{
    text_t * tt=malloc(sizeof(text_t));
    tt->value=v;
    tt->p=doc->testo;
    doc->testo->n=tt;
    tt->n=NULL;
    doc->last=tt;
    doc->testo=tt;
    doc->index=i;
}

documento esegui_change(documento doc1,long int ind1, long int ind2){
    long int i;
    unsigned long int l;
    documento appoggio;

    if(labs(ind1-testa->index)<=labs(ind1-coda->index))
        doc1=testa;
    else
        doc1=coda;

    if(doc1->index<ind1) {
        while (doc1->index<ind1 && doc1->n!=NULL)
            doc1 = doc1->n;
    }
    if(doc1->index>ind1) {
        while (doc1->index>ind1 && doc1->p!=NULL)
            doc1 = doc1->p;
    }
    for(i=ind1;i<=ind2;i++){
        fgets(file,1030,stdin);
        l=strlen(file);
        file[l-1]='\0';
        l=l+5;
        if(doc1->index==i)
            inserisci_riga(doc1, file, i);
        else {
            appoggio = doc1->n;
            doc1->n = inizializza_documento(i);
            inserisci_riga(doc1->n, file, i);
            doc1->n->n = appoggio;
            doc1->n->p = doc1;
        }
        if(doc1->n!=NULL)
            if(doc1->n->index<=ind2)
                doc1 = doc1->n;

        file=file+l+1;
        /*file[0]='\0';
        file=file+1;*/
    }
    fgets(file,1030,stdin);//il punto in input
    file[1]='\0';
    file=file+strlen(file);
    return doc1;
}

//DELETE
void inserisci_riga_nulla(documento doc, long int i) //INSERISCE O MODIFICA CON NULL LA RIGA ALL'INDICE I
{
    documento doc1=doc;
    //printf("inserisco riga nulla");
    text_t * tt=malloc(sizeof(text_t));
    if(doc1==NULL)
        doc1=inizializza_documento(i);
    tt->value=NULL;
    tt->p=doc1->testo;
    tt->n=NULL;
    doc1->testo->n=tt;
    doc1->testo=tt;
    doc1->last=tt;
    doc1->index=i;
}
int esegui_delete(documento doc,long int ind1, long int ind2){
    documento doc1,doc2;
    doc1=doc;
    long int eliminare=0;

    /*if(labs(ind1-testa->index)<=labs(ind1-coda->index))
        doc1=testa;
    else
        doc1=coda;*/

    if(doc1->index<ind1) {//posiziono la testina di scrittura
        while (doc1->index<ind1 && doc1->n!=NULL)
            doc1 = doc1->n;
    }
    if(doc1->index>ind1) {
        while (doc1->index>ind1 && doc1->p!=NULL)
            doc1 = doc1->p;
    }

    doc2=doc1;


    while(doc2->index<=ind2){//calcolo quante righe devo effettivamente cancellare
        if(doc2->testo->value!=NULL)
            eliminare = eliminare + 1;
        doc2=doc2->n;
        if(doc2==NULL)
            break;
    }
    if(eliminare==0)
        return 1;
    //printf("eccomi");

    if(doc2!=NULL)
        while(doc2->index<(ind1+eliminare)) {//posiziono la testina di lettura
            doc2 = doc2->n;
            if(doc2==NULL)
                break;
        }
    while(doc2!=NULL){ //scalano le righe fino alla fine del documento
        if (doc2 == NULL)
            inserisci_riga_nulla(doc1, doc1->index);
        else {
            if ((doc2->testo == NULL || doc2->testo->value==NULL)&&doc2->index>ind2)
                inserisci_riga_nulla(doc1, doc1->index);
            else
                inserisci_riga(doc1, doc2->testo->value, doc1->index);
            doc2=doc2->n;
        }
        doc1=doc1->n;
    }
    while(doc1!=NULL){
        //if(doc1->testo->value!=NULL||doc1->index>ind2)
        inserisci_riga_nulla(doc1, doc1->index);
        doc1=doc1->n;
    }
    return 0;
}

//UNDO
storico esegui_undo(documento doc, storico crono, long int i){
    long int x=0,i1,i2;
    documento doc1=doc;
    //printf("%li u \n",i);
    while(crono!=NULL&&x<i){
        i1=crono->i1;
        i2=crono->i2;

        if(labs(i1-testa->index)<=labs(i1-coda->index))
            doc1=testa;
        else
            doc1=coda;

        //printf("undo di:%li,%li%c\n",i1,i2,crono->input);
        if(crono->i1!=-2) {
            if (doc1->index < i1) {
                while (doc1->index < i1 && doc1->n != NULL)
                    doc1 = doc1->n;
            }
            else if (doc1->index > i1) {
                while (doc1->index > i1 && doc1->p != NULL)
                    doc1 = doc1->p;
            }
            while (doc1->index <= i2) {
                doc1->testo = doc1->testo->p;
                doc1 = doc1->n;
                if (doc1 == NULL)
                    break;
            }
        }
        if(crono->p)
            crono=crono->p;
        x=x+1;
    }
    return crono;
}
//REDO
storico esegui_redo(documento doc, storico crono, long int i){
    long int x=0,i1,i2;
    documento doc1=doc;
    crono=crono->n;
    while(crono!=NULL&&x<i){
        i1 = crono->i1;
        i2 = crono->i2;

        if(labs(i1-testa->index)<=labs(i1-coda->index))
            doc1=testa;
        else
            doc1=coda;
        //printf("redo di: %li,%li%c \n",i1,i2,crono->input);

        if(crono->i1!=-2) {
            if (doc1->index < i1) {
                while (doc1->index < i1 && doc1->n != NULL)
                    doc1 = doc1->n;
            }
            else if (doc1->index > i1) {
                while (doc1->index > i1 && doc1->p != NULL)
                    doc1 = doc1->p;
            }

            while (doc1->index <= i2) {
                doc1->testo = doc1->testo->n;
                doc1 = doc1->n;
                if (doc1 == NULL)
                    break;
            }
        }

        if(crono->n==NULL)
            break;
        if(x!=i-1) {
            //printf("ci sono\n");
            crono = crono->n;
        }
        x=x+1;
    }
    return crono;
}

void reset_undo(documento docr){
    while(docr!=NULL) {
        docr->testo = docr->first;
        docr=docr->n;
    }
}

void reset_redo(documento docr){
    while(docr!=NULL) {
        docr->testo = docr->last;
        docr=docr->n;
    }
}

void consolida_valori(documento docb){
    //puts("consolido");
    while(docb){
        if(docb->last!=docb->testo)
            docb->last=docb->testo;
        docb=docb->n;
    }
}

//FUNZIONI GENERICHE
documento esegui_comando(char *s, documento doc, storico * cronologia){
    long int ind1,ind2,ind3,nu=0,nr=0,rd_init=rd,ud_init=ud;
    char * r;
    char c,c1;
    int esci=0,inutile;
    //file=file+strlen(s)+1;
    r=s;
    ind1=strtol(r,&r,10);//ind1 è il primo riferimento
    c=*r;

    if((ud==0&&c=='u')||(rd==0&&c=='r')) //se sto facendo redo o undo impossibili le ignoro
        return doc;

    if(c=='u'||c=='r'){//inizia serie di undo e redo consecutivi
        char * w1;

        if(c=='r') {
            nr = ind1;
            if(nr>rd)
                nr=rd;
            ud=ud+nr;
            rd=rd-nr;
        }
        else {
            nu = ind1;
            if(nu>ud)
                nu=ud;
            ud=ud-nu;
            rd=rd+nu;
        }

        while(esci==0){
            fgets(file,1030,stdin);
            //w=strtok(file,"\n");
            w1=file;
            ind3=strtol(w1,&w1,10);
            c1=*w1;

            if((ud==0&&c1=='u')||(rd==0&&c1=='r')) //se sto facendo redo o undo impossibili le ignoro
                continue;

            if(c1==',') {
                esci = 1;
                continue;
            }

            if(c1=='q')
                exit(0);

            if(c1=='r') {
                if(ind3>rd)
                    ind3=rd;
                rd=rd-ind3;
                ud=ud+ind3;
                nr=nr+ind3;
                continue;
            }
            //ho undo
            if(ind3>ud)
                ind3=ud;
            ud=ud-ind3;
            rd=rd+ind3;
            nu=nu+ind3;
        }

        /*if(nr>nu&&(nr-nu)>=rd)
            exit(3);*/

        //undo di tutto
        if(nu>nr&&(nu-nr)>=ud_init){
            //puts("undo di tutto");
            //printf("ud:%li rd:%li\n",ud,rd);
            reset_undo(testa);
            *cronologia=cronotesta;

            //rd=ud_init;
            ud=0;

            doc=esegui_comando(file,doc,cronologia);
            return doc;
        }

        //redo di tutto
        if(nr>nu&&(nr-nu)>=rd_init){
            //puts("redo di tutto");
            //printf("nr:%li nu:%li rd:%li\n",nr,nu,rd);
            reset_redo(testa);
            *cronologia=cronocoda;

            //ud=rd_init;
            rd=0;

            doc=esegui_comando(file,doc,cronologia);
            return doc;
        }

        if(nu!=nr) {
            if (nu > nr) {
                if((nu-nr)<(ud_init/2))
                    *cronologia = esegui_undo(doc, *cronologia, nu - nr);
                else{
                    reset_undo(testa);
                    *cronologia=cronotesta;
                    //ud=0;
                    *cronologia = esegui_redo(doc, *cronologia, ud_init - (nu - nr));
                }
            }

            else {
                if((nr-nu)<(rd_init/2))
                    *cronologia = esegui_redo(doc, *cronologia, nr - nu);
                else{
                    reset_redo(testa);
                    *cronologia=cronocoda;
                    //rd=0;
                    *cronologia = esegui_undo(doc, *cronologia, rd_init - (nr - nu));
                }
            }

            //cronocoda=*cronologia;
        }

        doc=esegui_comando(file,doc,cronologia);
        return doc;
    }

    r=r+1;
    ind2=strtol(r,&r,10);//ind2 è il secondo riferimento

    c=*r;

    if((*cronologia)->n!=NULL)
        sentinella=1;
    if(c=='p'){//ho una print
        if(ind1==1)
            esegui_print(testa,ind1,ind2);
        else
            esegui_print(doc,ind1,ind2);
        if(sentinella==1&&(*cronologia)->n==NULL){
            consolida_valori(testa);
            sentinella=0;
        }
        return doc;
    }


    if(c=='d'){//ho un delete
        if(ind1==1)
            inutile=esegui_delete(testa,ind1,ind2);
        else
            inutile=esegui_delete(doc,ind1,ind2);
        if(inutile)
            ind1=-2;
        *cronologia=aggiungi_storico(*cronologia,ind1,coda->index);
        cronocoda=*cronologia;
        rd=0;
        /*while(doc->testo->value==NULL) { //mi riposiziono alla fine del documento
            if(doc->p==NULL)
                break;
            doc = doc->p;
        }*/
        if(sentinella==1&&(*cronologia)->n==NULL){
            consolida_valori(testa);
            sentinella=0;
        }
        return doc;
    }

    //ho una change
    if(ind1==1)
        doc=esegui_change(testa,ind1,ind2);
    else
        doc=esegui_change(doc,ind1,ind2);
    *cronologia=aggiungi_storico(*cronologia,ind1,ind2);
    cronocoda=*cronologia;
    rd=0;
    if(sentinella==1&&(*cronologia)->n==NULL){
        consolida_valori(testa);
        sentinella=0;
    }

    return doc;
}


//inizio main
int main() {
    storico cronologia;
    comando_t comando;
    comando.i1=-1;
    comando.i2=-1;
    comando.p=NULL;
    comando.n=NULL;
    cronologia=&comando;
    cronotesta=cronologia;
    cronocoda=cronologia;

    documento doc;
    text_t tt;
    riga_t rr;
    tt.value=NULL;
    tt.n=NULL;
    tt.p=NULL;
    rr.n=NULL;
    rr.p=NULL;
    rr.index=1;
    rr.testo=&tt;
    rr.first=&tt;
    rr.last=&tt;
    doc=&rr;
    testa=doc;
    coda=doc;
    char * inizio_file;
    int size=200000000;
    file=calloc(1,size);
    inizio_file=file;
    //s=calloc(1,1030);
    //fread(file,200000000,1,stdin);
    do {
        fgets(file,1030,stdin);
        if(strcmp(file,"q\n")==0)
            return 0;
        file[strlen(file)-1]='\0';
        doc=esegui_comando(file,doc,&cronologia);
        if((double)((file-inizio_file))>(0.90*size)){
            size=size*2;
            inizio_file=realloc(inizio_file,(unsigned long)size);
            }
    }while(1);
}